/*
** EPITECH PROJECT, 2024
** DisplayTile.cpp
** File description:
** zappy_gui
*/

#include "DisplayTile.hpp"

zappy::render3d::DisplayTile::DisplayTile(Assets &assets) : _baseImage(assets.placeholderImage) {}

zappy::render3d::DisplayTile::~DisplayTile() = default;

void zappy::render3d::DisplayTile::computeTileImage(zappy::render3d::Camera &camera)
{
    // Create a scaled version of the _baseImage to match the unitary size
    sf::Image _scaledImage;
    unsigned int sizeX = _baseImage.getSize().x;
    unsigned int sizeY = _baseImage.getSize().y;
    unsigned int maxScale = std::max(sizeX, sizeY);

    _scaledImage.create(sizeX * camera.unitaryPixelsSize / maxScale, sizeY * camera.unitaryPixelsSize / maxScale,
                        sf::Color::Transparent);

    double xRatio = static_cast<double>(_baseImage.getSize().x) / _scaledImage.getSize().x;
    double yRatio = static_cast<double>(_baseImage.getSize().y) / _scaledImage.getSize().y;

    for (unsigned int i = 0; i < sizeX; i++)
    {
        for (unsigned int j = 0; j < sizeY; j++)
        {
            _scaledImage.setPixel(i / xRatio, j / yRatio, _baseImage.getPixel(i, j));
        }
    }

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
    for (unsigned int i = 0; i < size.x; i++) {
        for (unsigned int j = 0; j < size.y; j++) {
            math::Point3D point = camera.projectPoint(math::Point3D(i, j, 0));
            unsigned int px = static_cast<unsigned int>(point.x - minWidth);
            unsigned int py = static_cast<unsigned int>(point.y - minHeight);
            if (px < imageWidth && py < imageHeight)
                image.setPixel(px, py, _scaledImage.getPixel(i, j));
        }
    }

    _displayTexture.create(1, 1);

    // Draw the _baseImage on the new _baseImage
    if (!_displayTexture.loadFromImage(image)) {
        std::cerr << "Error loading _baseImage from image" << std::endl;
    }
}

sf::Texture &zappy::render3d::DisplayTile::getTexture()
{
    return _displayTexture;
}
