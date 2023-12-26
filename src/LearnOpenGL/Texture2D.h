#pragma once
#include <string>

enum ColorValue
{
    RGB,
    RGBA
};

enum WrappingMethod
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder
};

class Texture2D
{
public:
    int32_t TextureId;
    int32_t Width, Height;

    Texture2D(const std::string& path, ColorValue colorValue = ColorValue::RGBA, WrappingMethod wrappingMethod = WrappingMethod::Repeat);
};

