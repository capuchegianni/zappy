/*
** EPITECH PROJECT, 2024
** Tile.cpp
** File description:
** zappy_gui
*/

#include "Tile.hpp"

zappy::render3d::TileDrawables::TileDrawables(sf::Image &image) : baseImage(image) {}

zappy::render3d::TileDrawables::~TileDrawables() = default;

zappy::render3d::Tile::Tile(Assets &assets) : _drawables(assets.placeholderImage) {}

zappy::render3d::Tile::~Tile() = default;

void zappy::render3d::Tile::update(zappy::Box &box)
{
    x = box.x;
    y = box.y;
}

void zappy::render3d::Tile::setTileTexture(sf::Texture &texture)
{
    _drawables.displayTexture = texture;
}

void zappy::render3d::Tile::computeTileImage(zappy::render3d::Camera &camera)
{
    // Project tile corners to screen
    sf::Vector2<unsigned int> size = _drawables.baseImage.getSize();

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

    // Set corner pixels (ensure they are within image bounds)
    if (topLeft.x < imageWidth && topLeft.y < imageHeight)
        image.setPixel(topLeft.x, topLeft.y, sf::Color::White);
    if (topRight.x < imageWidth && topRight.y < imageHeight)
        image.setPixel(topRight.x, topRight.y, sf::Color::White);
    if (bottomLeft.x < imageWidth && bottomLeft.y < imageHeight)
        image.setPixel(bottomLeft.x, bottomLeft.y, sf::Color::White);
    if (bottomRight.x < imageWidth && bottomRight.y < imageHeight)
        image.setPixel(bottomRight.x, bottomRight.y, sf::Color::White);

    // Draw points for the entire tile
    for (unsigned int i = 0; i < size.x; i++) {
        for (unsigned int j = 0; j < size.y; j++) {
            math::Point3D point = camera.projectPoint(math::Point3D(i, j, 0));
            unsigned int px = static_cast<unsigned int>(point.x - minWidth);
            unsigned int py = static_cast<unsigned int>(point.y - minHeight);
            if (px < imageWidth && py < imageHeight)
                image.setPixel(px, py, _drawables.baseImage.getPixel(i, j));
        }
    }

    _drawables.displayTexture.create(1, 1);

    // Draw the baseImage on the new baseImage
    if (!_drawables.displayTexture.loadFromImage(image)) {
        std::cerr << "Error loading baseImage from image" << std::endl;
    }
    _drawables.sprite = sf::Sprite(_drawables.displayTexture);
    _drawables.sprite.setPosition(150, 150);
}


void zappy::render3d::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.sprite, states);
}
