/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2018 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#include <cstring>
#include <mango/core/pointer.hpp>
#include <mango/core/exception.hpp>
#include <mango/image/image.hpp>
//#include <mango/opengl/opengl.hpp>

#define ID "[ImageDecoder.KTX] "

namespace
{
    using namespace mango;

    // KTX Format Specification:
	// http://www.khronos.org/opengles/sdk/tools/KTX/file_format_spec/

    // OpenGL glTexImagewD specification:
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml

    // ----------------------------------------------------------------------------
    // format conversion
    // ----------------------------------------------------------------------------

#if 0

#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_DOUBLE                         0x140A
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49
#define GL_COMPRESSED_RED                 0x8225
#define GL_COMPRESSED_RG                  0x8226
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#define GL_RGB9_E5                        0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E

#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RED_INTEGER                    0x8D94
#define GL_GREEN_INTEGER                  0x8D95
#define GL_BLUE_INTEGER                   0x8D96
#define GL_RGB_INTEGER                    0x8D98
#define GL_RGBA_INTEGER                   0x8D99
#define GL_BGR_INTEGER                    0x8D9A
#define GL_BGRA_INTEGER                   0x8D9B

#define GL_DEPTH_COMPONENT32F             0x8CAC
#define GL_DEPTH32F_STENCIL8              0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD

#define GL_DEPTH_STENCIL                  0x84F9
#define GL_UNSIGNED_INT_24_8              0x84FA
#define GL_DEPTH24_STENCIL8               0x88F0

#define GL_STENCIL_INDEX1                 0x8D46
#define GL_STENCIL_INDEX4                 0x8D47
#define GL_STENCIL_INDEX8                 0x8D48
#define GL_STENCIL_INDEX16                0x8D49

#define GL_HALF_FLOAT                     0x140B

#define GL_COMPRESSED_RED_RGTC1           0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1    0x8DBC
#define GL_COMPRESSED_RG_RGTC2            0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2     0x8DBE
#define GL_RG                             0x8227
#define GL_RG_INTEGER                     0x8228
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C

#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16_SNORM                      0x8F98
#define GL_RG16_SNORM                     0x8F99
#define GL_RGB16_SNORM                    0x8F9A
#define GL_RGBA16_SNORM                   0x8F9B
#define GL_SIGNED_NORMALIZED              0x8F9C

#define GL_INT_2_10_10_10_REV             0x8D9F

#define GL_FIXED                          0x140C

#define GL_RGB565                         0x8D62

#define GL_COMPRESSED_RGBA_BPTC_UNORM     0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8E8F

#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_SRGB8_ETC2          0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_R11_EAC             0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#define GL_COMPRESSED_RG11_EAC            0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC     0x9273

#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8E8F

#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD

#define GL_RGB_422_APPLE                  0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#define GL_RGB_RAW_422_APPLE              0x8A51

#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3

#endif

/*
    enum OpenGLMacros : u32
    {
        GL_UNSIGNED_BYTE = 0,
        GL_BYTE,
        GL_UNSIGNED_SHORT,
        GL_SHORT,
        GL_UNSIGNED_INT,
        GL_INT,
        GL_HALF_FLOAT,
        GL_FLOAT,
        GL_UNSIGNED_BYTE_3_3_2,
        GL_UNSIGNED_BYTE_2_3_3_REV,
        GL_UNSIGNED_SHORT_5_6_5,
        GL_UNSIGNED_SHORT_5_6_5_REV,
        GL_UNSIGNED_SHORT_4_4_4_4,
        GL_UNSIGNED_SHORT_4_4_4_4_REV,
        GL_UNSIGNED_SHORT_5_5_5_1,
        GL_UNSIGNED_SHORT_1_5_5_5_REV,
        GL_UNSIGNED_INT_8_8_8_8,
        GL_UNSIGNED_INT_8_8_8_8_REV,
        GL_UNSIGNED_INT_10_10_10_2,
        GL_UNSIGNED_INT_2_10_10_10_REV,
    };
*/
 
    bool resolve_format(u32 type, u32 format)
    {
        switch (type)
        {
        }

        /*

        // RED, RG, RGB, RGBA
        GL_UNSIGNED_BYTE
        GL_BYTE
        GL_UNSIGNED_SHORT
        GL_SHORT
        GL_UNSIGNED_INT
        GL_INT
        GL_HALF_FLOAT
        GL_FLOAT

        // RGB
        GL_UNSIGNED_BYTE_3_3_2
        GL_UNSIGNED_BYTE_2_3_3_REV
        GL_UNSIGNED_SHORT_5_6_5
        GL_UNSIGNED_SHORT_5_6_5_REV

        // RGBA, BGRA
        GL_UNSIGNED_SHORT_4_4_4_4
        GL_UNSIGNED_SHORT_4_4_4_4_REV
        GL_UNSIGNED_SHORT_5_5_5_1
        GL_UNSIGNED_SHORT_1_5_5_5_REV
        GL_UNSIGNED_INT_8_8_8_8
        GL_UNSIGNED_INT_8_8_8_8_REV
        GL_UNSIGNED_INT_10_10_10_2
        GL_UNSIGNED_INT_2_10_10_10_REV

        */

        return false;
    }


    /*
    glInternalFormat: 1908        GL_RGBA
    glFormat: 1908                GL_RGBA
    glType: 1401                  GL_UNSIGNED_BYTE
    */

#if 0

glType:
    0 - compressed texture

    GL_UNSIGNED_BYTE
    GL_BYTE
    GL_UNSIGNED_SHORT
    GL_SHORT
    GL_UNSIGNED_INT
    GL_INT
    GL_HALF_FLOAT
    GL_FLOAT
    GL_UNSIGNED_BYTE_3_3_2
    GL_UNSIGNED_BYTE_2_3_3_REV
    GL_UNSIGNED_SHORT_5_6_5
    GL_UNSIGNED_SHORT_5_6_5_REV
    GL_UNSIGNED_SHORT_4_4_4_4
    GL_UNSIGNED_SHORT_4_4_4_4_REV
    GL_UNSIGNED_SHORT_5_5_5_1
    GL_UNSIGNED_SHORT_1_5_5_5_REV
    GL_UNSIGNED_INT_8_8_8_8
    GL_UNSIGNED_INT_8_8_8_8_REV
    GL_UNSIGNED_INT_10_10_10_2
    GL_UNSIGNED_INT_2_10_10_10_REV
    GL_UNSIGNED_INT_24_8
    GL_UNSIGNED_INT_10F_11F_11F_REV
    GL_UNSIGNED_INT_5_9_9_9_REV
    GL_FLOAT_32_UNSIGNED_INT_24_8_REV


glTypeSize:
    number of bytes to byteswap (1 - no endian conversion, 2 - 16 bits, 4 - 32 bits)


glFormat:
    0 - compressed texture

    GL_STENCIL_INDEX
    GL_DEPTH_COMPONENT
    GL_DEPTH_STENCIL
    GL_RED
    GL_GREEN
    GL_BLUE
    GL_RG
    GL_RGB
    GL_RGBA
    GL_BGR
    GL_BGRA
    GL_RED_INTEGER
    GL_GREEN_INTEGER
    GL_BLUE_INTEGER
    GL_RG_INTEGER
    GL_RGB_INTEGER
    GL_RGBA_INTEGER
    GL_BGR_INTEGER
    GL_BGRA_INTEGER

glInternalFormat:

    uncompressed:

    RGB16
    RGB16_SNORM
    RGBA2
    RGBA4
    RGB5_A1
    RGBA8
    RGBA8_SNORM
    RGB10_A2
    RGB10_A2UI
    RGBA12
    RGBA16
    RGBA16_SNORM
    SRGB8
    SRGB8_ALPHA8

    R16F
    RG16F
    RGB16F
    RGBA16F

    R32F
    RG32F
    RGB32F
    RGBA32F

    R11F_G11F_B10F
    RGB9_E5

    R8I
    R8UI
    R16I
    R16UI
    R32I
    R32UI
    RG8I
    RG8UI
    RG16I
    RG16UI
    RG32I
    RG32UI
    RGB8I
    RGB8UI
    RGB16I
    RGB16UI
    RGB32I
    RGB32UI
    RGBA8I
    RGBA8UI
    RGBA16I
    RGBA16UI
    RGBA32I
    RGBA32UI

    DEPTH_COMPONENT16
    DEPTH_COMPONENT24
    DEPTH_COMPONENT32
    DEPTH_COMPONENT32F
    DEPTH24_STENCIL8
    DEPTH32F_STENCIL8
    STENCIL_INDEX1
    STENCIL_INDEX4
    STENCIL_INDEX8
    STENCIL_INDEX16

glBaseInternalFormat:

    DEPTH_COMPONENT
    DEPTH_STENCIL
    RED
    RG
    RGB
    RGBA
    STENCIL_INDEX

#endif

    // ----------------------------------------------------------------------------
    // header
    // ----------------------------------------------------------------------------

    struct HeaderKTX
    {
		u8 identifier[12];
		u32 endianness;
		u32 glType;
		u32 glTypeSize;
		u32 glFormat;
		u32 glInternalFormat;
		u32 glBaseInternalFormat;
		u32 pixelWidth;
		u32 pixelHeight;
		u32 pixelDepth;
		u32 numberOfArrayElements;
		u32 numberOfFaces;
		u32 numberOfMipmapLevels;
		u32 bytesOfKeyValueData;

		HeaderKTX(Memory memory)
		{
			const u8 ktxIdentifier[] =
			{
				0xab, 0x4b, 0x54, 0x58, 0x20, 0x31,
                0x31, 0xbb, 0x0d, 0x0a, 0x1a, 0x0a
			};

			std::memcpy(this, memory.address, sizeof(HeaderKTX));

			if (std::memcmp(ktxIdentifier, identifier, 12))
			{
                MANGO_EXCEPTION(ID"Incorrect identifier.");
			}

			if (endianness != 0x04030201)
			{
				if (endianness != 0x01020304)
				{
                    MANGO_EXCEPTION(ID"Incorrect endianness.");
				}
				else
				{
					// convert endianness
					glType = byteswap(glType);
					glTypeSize = byteswap(glTypeSize);
					glFormat = byteswap(glFormat);
					glInternalFormat = byteswap(glInternalFormat);
					glBaseInternalFormat = byteswap(glBaseInternalFormat);
					pixelWidth = byteswap(pixelWidth);
					pixelHeight = byteswap(pixelHeight);
					pixelDepth = byteswap(pixelDepth);
					numberOfArrayElements = byteswap(numberOfArrayElements);
					numberOfFaces = byteswap(numberOfFaces);
					numberOfMipmapLevels = byteswap(numberOfMipmapLevels);
					bytesOfKeyValueData = byteswap(bytesOfKeyValueData);
				}
			}

#if 0
            printf("endianness: %x\n", endianness);
            printf("glType: %x\n", glType);
            printf("glTypeSize: %x\n", glTypeSize);
            printf("glFormat: %x\n", glFormat);
            printf("glInternalFormat: %x\n", glInternalFormat);
            printf("glBaseInternalFormat: %x\n", glBaseInternalFormat);
            printf("pixelWidth: %d\n", pixelWidth);
            printf("pixelHeight: %d\n", pixelHeight);
            printf("pixelDepth: %d\n", pixelDepth);
            printf("numberOfArrayElements: %d\n", numberOfArrayElements);
            printf("numberOfFaces: %d\n", numberOfFaces);
            printf("numberOfMipmapLevels: %d\n", numberOfMipmapLevels);
            printf("bytesOfKeyValueData: %d\n", bytesOfKeyValueData);
#endif

            if (numberOfFaces != 1 && numberOfFaces != 6)
            {
                MANGO_EXCEPTION(ID"Incorrect number of faces.");
            }

            if (numberOfArrayElements != 0)
            {
                MANGO_EXCEPTION(ID"Incorrect number of array elements (not supported).");
            }

            numberOfMipmapLevels = std::max(1U, numberOfMipmapLevels);
		}

		~HeaderKTX()
		{
		}

        u32 read32(const u8* p) const
        {
            u32 value = uload32(p);
            if (endianness != 0x04030201)
            {
                value = byteswap(value);
            }
            return value;
        }

        TextureCompression computeFormat(Format& format) const
        {
			TextureCompression compression = opengl::getTextureCompression(glInternalFormat);

            if (compression != TextureCompression::NONE)
            {
				TextureCompressionInfo info(compression);
                format = info.format;
            }
            else
            {
#if 0
                // TODO: make this work w/o OpenGL
                const opengl::InternalFormat* info = opengl::getInternalFormat(glInternalFormat);
                if (info)
                {
                    format = info->format;
                }
                else
#endif
                {
                    format = FORMAT_NONE;
                }
            }

            return compression;
        }

		Memory getMemory(Memory memory, int level, int depth, int face) const
		{
			u8* address = memory.address;
			address += sizeof(HeaderKTX) + bytesOfKeyValueData;

            const int maxLevel = int(numberOfMipmapLevels);
            const int maxFace = int(numberOfFaces);

            MANGO_UNREFERENCED_PARAMETER(depth); // TODO

            Memory data;

            for (int iLevel = 0; iLevel < maxLevel; ++iLevel)
            {
                const int imageSize = read32(address);
                const int imageSizeRounded = (imageSize + 3) & ~3;
                address += 4;

                for (int iFace = 0; iFace < maxFace; ++iFace)
                {
                    if (iLevel == level && iFace == face)
                    {
                        // Store selected address
                        data = Memory(address, imageSizeRounded);
                    }

                    address += imageSizeRounded;
                }
            }

            return data;
        }
    };

    // ------------------------------------------------------------
    // ImageDecoder
    // ------------------------------------------------------------

    struct Interface : ImageDecoderInterface
    {
        Memory m_memory;
        HeaderKTX m_header;

        Interface(Memory memory)
            : m_memory(memory)
            , m_header(memory)
        {
        }

        ~Interface()
        {
        }

        ImageHeader header() override
        {
            ImageHeader header;

            header.width   = m_header.pixelWidth;
            header.height  = m_header.pixelHeight;
            header.depth   = 0;
            header.levels  = m_header.numberOfMipmapLevels;
            header.faces   = m_header.numberOfFaces;
			header.palette = false;
            header.format  = FORMAT_NONE;
            header.compression = m_header.computeFormat(header.format);

            return header;
        }

        Memory memory(int level, int depth, int face) override
        {
            Memory data = m_header.getMemory(m_memory, level, depth, face);
            return data;
        }

        void decode(Surface& dest, Palette* palette, int level, int depth, int face) override
        {
            MANGO_UNREFERENCED_PARAMETER(palette);

            Memory data = m_header.getMemory(m_memory, level, depth, face);

            Format format;
            TextureCompressionInfo info = m_header.computeFormat(format);

            if (info.compression != TextureCompression::NONE)
            {
                info.decompress(dest, data);
            }
            else if (format != FORMAT_NONE)
            {
                int width = std::max(1U, m_header.pixelWidth >> level);
                int height = std::max(1U, m_header.pixelHeight >> level);
                int stride = width * format.bytes();
                Surface source(width, height, format, stride, data.address);
                dest.blit(0, 0, source);
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

    void registerImageDecoderKTX()
    {
        registerImageDecoder(createInterface, ".ktx");
    }

} // namespace mango
