/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
/*
    GIF decoder source: ImageMagick.
*/
#include <mango/core/pointer.hpp>
#include <mango/core/exception.hpp>
#include <mango/core/system.hpp>
#include <mango/image/image.hpp>

#define ID "[ImageDecoderGIF] "

namespace
{
    using namespace mango;

	// ------------------------------------------------------------
	// decoder
	// ------------------------------------------------------------

	// Specification:
	// https://www.w3.org/Graphics/GIF/spec-gif89a.txt

	enum
	{
		GIF_IMAGE      = 0x2c,
		GIF_EXTENSION  = 0x21,
		GIF_TERMINATE  = 0x3b
	};

	struct gif_logical_screen_descriptor
	{
		u16	width = 0;
		u16	height = 0;
		u8	packed = 0;
		u8	background = 0;
		u8  aspect = 0;
		u8* palette = nullptr;

        u8* read(u8* data, u8* end)
		{
			LittleEndianPointer p = data;

			if (p + 7 < end)
			{
                width      = p.read16();
                height     = p.read16();
                packed     = p.read8();
                background = p.read8();
                aspect     = p.read8();

                if (color_table_flag())
                {
                    palette = p;
                    p += color_table_size() * 3;
                }
			}

			return p;
		}

		int  color_table_size() const { return 1 << ((packed & 0x07) + 1); }
		bool sort_flag()        const { return (packed & 0x08) == 0x08; }
		int  color_resolution() const { return (packed >> 4) & 0x07; }
		bool color_table_flag() const { return (packed & 0x80) == 0x80; }
	};

	struct gif_image_descriptor
	{
		u16	left = 0;
		u16	top = 0;
		u16	width = 0;
		u16	height = 0;
		u8	field = 0;
		u8* palette = nullptr;

        u8* read(u8* data, u8* end)
		{
            LittleEndianPointer p = data;

            if (p + 9 < end)
            {
                left   = p.read16();
                top    = p.read16();
                width  = p.read16();
                height = p.read16();
                field  = p.read8();

                if (local_color_table())
                {
                    palette = p;
                    p += color_table_size() * 3;
                }
            }

			return p;
		}

		bool interlaced()        const { return (field & 0x40) != 0; }
		bool local_color_table() const { return (field & 0x80) != 0; }
		int  color_table_size()  const { return 1 << ((field & 0x07) + 1); }
	};

	u8* readBits(u8* data, u8* dest, int samples)
	{
        u8* p = data;

		const int MaxStackSize = 4096;

		u8 data_size = *p++;

		int clear = 1 << data_size;
		int end_of_information = clear + 1;
		int available = clear + 2;

		int code_size = data_size + 1;
		int code_mask = (1 << code_size) - 1;
		int old_code = -1;

		u16 prefix[MaxStackSize];
		u8 suffix[MaxStackSize];

		u8 pixel_stack[MaxStackSize + 1];
		u8* top_stack = pixel_stack;

		for (int code = 0; code < clear; ++code)
		{
			prefix[code] = 0;
			suffix[code] = u8(code);
		}

		// decode gif pixel stream
		int bits = 0;
		int count = 0;
		u32 datum = 0;
		u8 first = 0;

		u8* q = dest;
		u8* qend = dest + samples;

		u8 packet[256];
		u8* c = nullptr;

		while (q < qend)
		{
			if (top_stack == pixel_stack)
			{
				if (bits < code_size)
				{
					// load bytes until there is enough bits for a code
					if (!count)
					{
						// read a new data block
						u8 block_size = *p++;
						count = block_size;

						if (count > 0)
						{
							std::memcpy(packet, p, count);
							p += count;
						}
						else
						{
							break;
						}

						c = packet;
					}

					datum += (*c++) << bits;
					bits += 8;
					--count;
					continue;
				}

				// get the next code
				int code = datum & code_mask;
				datum >>= code_size;
				bits -= code_size;

				// interpret the code
				if ((code > available) || (code == end_of_information))
				{
					break;
				}

				if (code == clear)
				{
					// reset decoder
					code_size = data_size + 1;
					code_mask = (1 << code_size) - 1;
					available = clear + 2;
					old_code = -1;
					continue;
				}

				if (old_code == -1)
				{
					*top_stack++ = suffix[code];
					old_code = code;
					first = u8(code);
					continue;
				}

				int in_code = code;

				if (code >= available)
				{
					*top_stack++ = first;
					code = old_code;
				}

				while (code >= clear)
				{
					*top_stack++ = suffix[code];
					code = prefix[code];
				}

				first = suffix[code];

				// add a new string to the string table
				if (available >= MaxStackSize)
				{
					break;
				}

				*top_stack++ = first;
				prefix[available] = u16(old_code);
				suffix[available] = first;
				++available;

				if (!(available & code_mask) && (available < MaxStackSize))
				{
					++code_size;
					code_mask += available;
				}

				old_code = in_code;
			}

			// write sample
			*q++ = *(--top_stack);
		}

		// read the terminator
		u8 terminator = *p++;

        if (terminator != 0)
		{
			// There are files with incorrect terminator; let them pass silently
			//MANGO_EXCEPTION(ID"Terminator missing from the gif stream.");
		}

		return p;
	}

	void deinterlace(u8* dest, u8* buffer, int width, int height)
	{
		static const int interlace_rate[] = { 8, 8, 4, 2 };
		static const int interlace_start[] = { 0, 4, 2, 1 };

		for (int pass = 0; pass < 4; ++pass)
		{
			const int rate = interlace_rate[pass];
			int j =  interlace_start[pass];

			while (j < height)
			{
				u8* d = dest + j * width;
				std::memcpy(d, buffer, width);
				buffer += width;
				j += rate;
			}
		}
	}

    void blit_raw(Surface& surface, const u8* bits, u8 transparent)
	{
		int width = surface.width;
		int height = surface.height;

        for (int y = 0; y < height; ++y)
        {
            u8* dest = surface.address<u8>(0, y);
            for (int x = 0; x < width; ++x)
            {
				u8 sample = bits[x];
				if (sample != transparent)
				{
					dest[x] = sample;
				}
            }
            bits += width;
        }
	}

    void blit_palette(Surface& surface, const u8* bits, const Palette& palette)
    {
		int width = surface.width;
		int height = surface.height;

        for (int y = 0; y < height; ++y)
        {
            u32* dest = surface.address<u32>(0, y);
            for (int x = 0; x < width; ++x)
            {
				ColorBGRA color = palette[bits[x]];
				if (color.a)
				{
					dest[x] = color;
				}
            }
            bits += width;
        }
    }

    u8* read_image(u8* data, u8* end, const gif_logical_screen_descriptor& screen_desc, Surface& surface, Palette* ptr_palette)
    {
		gif_image_descriptor image_desc;
        data = image_desc.read(data, end);

		Palette palette;

		// choose palette
		if (image_desc.local_color_table())
		{
			// local palette
			palette.size = image_desc.color_table_size();

			for (u32 i = 0; i < palette.size; ++i)
			{
            	u32 r = image_desc.palette[i * 3 + 0];
            	u32 g = image_desc.palette[i * 3 + 1];
            	u32 b = image_desc.palette[i * 3 + 2];
            	palette[i] = ColorBGRA(r, g, b, 0xff);
			}
		}
		else
		{
			// global palette
			palette.size = screen_desc.color_table_size();

			for (u32 i = 0; i < palette.size; ++i)
			{
            	u32 r = screen_desc.palette[i * 3 + 0];
            	u32 g = screen_desc.palette[i * 3 + 1];
            	u32 b = screen_desc.palette[i * 3 + 2];
            	palette[i] = ColorBGRA(r, g, b, 0xff);
			}
		}

		// translucent color
		palette[screen_desc.background].a = 0;

        int width = image_desc.width;
        int height = image_desc.height;

		// decode gif bit stream
		int samples = width * height;
		u8* bits = new u8[samples];
		data = readBits(data, bits, samples);

        // deinterlace
		if (image_desc.interlaced())
		{
            u8* temp = new u8[width * height];
			deinterlace(temp, bits, width, height);
            delete[] bits;
            bits = temp;
		}

		if (ptr_palette)
		{
			*ptr_palette = palette;

			int x = image_desc.left;
			int y = image_desc.top;
			Surface temp(surface, x, y, width, height);
			blit_raw(temp, bits, screen_desc.background);
		}
		else
		{
			int x = image_desc.left;
			int y = image_desc.top;
			Surface temp(surface, x, y, width, height);
			blit_palette(temp, bits, palette);
		}

		delete[] bits;
		return data;
    }

	u8* read_extension(u8* data)
	{
        u8* p = data;
		++p;

		for (;;)
		{
			u8 size = *p++;
			p += size;
			if (!size) break;
		}

		return p;
	}

    u8* read_magic(u8* data, u8* end)
    {
		if (data + 6 >= end)
		{
			MANGO_EXCEPTION(ID"Out of data.");
		}

		const char* magic = reinterpret_cast<const char*>(data);
        data += 6;

		if (std::strncmp(magic, "GIF87a", 6) && std::strncmp(magic, "GIF89a", 6))
		{
            MANGO_EXCEPTION(ID"Incorrect gif header, missing GIF87a or GIF89a identifier.");
		}

		return data;
    }

    u8* read_chunks(u8* data, u8* end, const gif_logical_screen_descriptor& screen_desc, Surface& surface, Palette* ptr_palette)
    {
        while (data < end)
		{
			u8 chunkID = *data++;

			switch (chunkID)
			{
				case GIF_EXTENSION:
					data = read_extension(data);
					break;

				case GIF_IMAGE:
                    data = read_image(data, end, screen_desc, surface, ptr_palette);
                    return data;

				case GIF_TERMINATE:
                    return nullptr;
			}
		}

		return nullptr;
    }

    // ------------------------------------------------------------
    // ImageDecoder
    // ------------------------------------------------------------

    struct Interface : ImageDecoderInterface
    {
        Memory m_memory;
		ImageHeader m_header;
        gif_logical_screen_descriptor m_screen_desc;

		std::unique_ptr<u8[]> m_image;
		int m_frame_counter = 0;

		u8* m_start;
		u8* m_end;
		u8* m_data;

        Interface(Memory memory)
        	: m_memory(memory)
            , m_image(nullptr)
        {
			m_start = m_memory.address;
			m_end = m_memory.address + m_memory.size;
            m_data = m_memory.address;

			m_data = read_magic(m_data, m_end);
            m_data = m_screen_desc.read(m_data, m_end);

            m_header.width   = m_screen_desc.width;
            m_header.height  = m_screen_desc.height;
            m_header.depth   = 0;
            m_header.levels  = 0;
            m_header.faces   = 0;
			m_header.palette = true;
            m_header.format  = FORMAT_B8G8R8A8;
            m_header.compression = TextureCompression::NONE;

			m_image.reset(new u8[m_header.width * m_header.height * 4]);
        }

        ~Interface()
        {
        }

        ImageHeader header() override
        {
            return m_header;
        }

        void decode(Surface& dest, Palette* ptr_palette, int level, int depth, int face) override
        {
            MANGO_UNREFERENCED_PARAMETER(level);
            MANGO_UNREFERENCED_PARAMETER(depth);
            MANGO_UNREFERENCED_PARAMETER(face);

			if (m_data)
			{
				if (ptr_palette)
				{
					Surface target(m_header.width, m_header.height, FORMAT_L8, m_header.width, m_image.get());
					m_data = read_chunks(m_data, m_end, m_screen_desc, target, ptr_palette);
					dest.blit(0, 0, target);
				}
				else
				{
					Surface target(m_header.width, m_header.height, FORMAT_B8G8R8A8, m_header.width * 4, m_image.get());
					m_data = read_chunks(m_data, m_end, m_screen_desc, target, ptr_palette);
					dest.blit(0, 0, target);
				}
			}

			if (m_data)
			{
				++m_frame_counter;
			}
			else
			{
				if (m_frame_counter > 1)
				{
					m_frame_counter = 0;
					m_data = m_start;

				}
			}
        }
    };

    ImageDecoderInterface* createInterface(Memory memory)
    {
        ImageDecoderInterface* x = new Interface(memory);
        return x;
    }

} // namespace

namespace mango
{

    void registerImageDecoderGIF()
    {
        registerImageDecoder(createInterface, ".gif");
    }

} // namespace mango
