/*
** EPITECH PROJECT, 2024
** DisplayTile.cpp
** File description:
** zappy_gui
*/

#include "DisplayTile.hpp"

zappy::render3d::DisplayTile::DisplayTile(sf::Image &tile) : _baseImage(tile) {}

zappy::render3d::DisplayTile::DisplayTile(const zappy::render3d::DisplayTile &other) : _baseImage(other._baseImage) {}

zappy::render3d::DisplayTile::~DisplayTile() = default;

void zappy::render3d::DisplayTile::computeTileImage(zappy::render3d::Camera &camera)
{
    resizeImage(camera);
    projectTile(camera);
}

sf::Texture &zappy::render3d::DisplayTile::getTexture()
{
    return _displayTexture;
}

void zappy::render3d::DisplayTile::resizeImage(zappy::render3d::Camera &camera)
{
    if (camera.unitaryPixelsSize != camera.unitaryPixelsSizeBackup)
    {
        sf::Texture originalTexture;
        if (!originalTexture.loadFromImage(_baseImage))
        {
            throw DisplayTileError("Error loading texture from image");
        }

        sf::Sprite sprite(originalTexture);

        // Set the desired size
        unsigned int desiredWidth = camera.unitaryPixelsSize;
        unsigned int desiredHeight = camera.unitaryPixelsSize;

        sf::RenderTexture renderTexture;
        if (!renderTexture.create(desiredWidth, desiredHeight)) {
            throw DisplayTileError("Error creating RenderTexture");
        }

        // Scale the sprite to fit the RenderTexture
        sprite.setScale(
            static_cast<float>(desiredWidth) / originalTexture.getSize().x,
            static_cast<float>(desiredHeight) / originalTexture.getSize().y
        );

        // Draw the sprite onto the RenderTexture
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(sprite);
        renderTexture.display();

        // Get the new texture
        sf::Texture newTexture = renderTexture.getTexture();

        _scaledImage = newTexture.copyToImage();
    }
}

void zappy::render3d::DisplayTile::projectTile(zappy::render3d::Camera &camera)
{
    if (camera.unitaryPixelsSize != camera.unitaryPixelsSizeBackup || camera.direction != camera.directionBackup)
    {
        // Project tile corners to screen
        sf::Vector2<unsigned int> size = _scaledImage.getSize();

        math::Point3D topLeft = camera.projectPoint(math::Point3D(0, 0, 0));
        math::Point3D topRight = camera.projectPoint(math::Point3D(size.x, 0, 0));
        math::Point3D bottomLeft = camera.projectPoint(math::Point3D(0, size.y, 0));
        math::Point3D bottomRight = camera.projectPoint(math::Point3D(size.x, size.y, 0));

        // Calculate the bounding box of the projected points
        double maxHeight = std::max({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});
        double minHeight = std::min({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});
        double maxWidth = std::max({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
        double minWidth = std::min({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});

        // Offset points to fit in the image
        topLeft = math::Point3D(topLeft.x - minWidth, topLeft.y - minHeight, 0);
        topRight = math::Point3D(topRight.x - minWidth, topRight.y - minHeight, 0);
        bottomLeft = math::Point3D(bottomLeft.x - minWidth, bottomLeft.y - minHeight, 0);
        bottomRight = math::Point3D(bottomRight.x - minWidth, bottomRight.y - minHeight, 0);

        // Create image with the calculated dimensions
        unsigned int imageWidth = static_cast<unsigned int>(maxWidth - minWidth + 1);
        unsigned int imageHeight = static_cast<unsigned int>(maxHeight - minHeight + 1);

        sf::Image image;
        image.create(imageWidth, imageHeight, sf::Color::Transparent);

        // Draw points for the entire tile
        for (unsigned int i = 0; i < size.x; i++)
        {
            for (unsigned int j = 0; j < size.y; j++)
            {
                math::Point3D point = camera.projectPoint(math::Point3D(i, j, 0));
                unsigned int px = static_cast<unsigned int>(point.x - minWidth);
                unsigned int py = static_cast<unsigned int>(point.y - minHeight);
                if (px < imageWidth && py < imageHeight)
                    image.setPixel(px, py, _scaledImage.getPixel(i, j));
            }
        }

        _displayTexture.create(1, 1);

        // Draw the _baseImage on the new _baseImage
        if (!_displayTexture.loadFromImage(image))
        {
            std::cerr << "Error loading _baseImage from image" << std::endl;
        }
    }
}
