/*
** EPITECH PROJECT, 2024
** Trantorien.cpp
** File description:
** zappy_gui
*/

#include "Trantorien.hpp"

zappy::TrantorienDrawables::TrantorienDrawables()
{
    body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
    body.setScale(1, 2);

    shadow.setFillColor(sf::Color(0, 0, 0, 70));
    shadow.setRadius(50);
    shadow.setOrigin(shadow.getGlobalBounds().width / 2, shadow.getGlobalBounds().height / 2);
}

zappy::TrantorienDrawables::~TrantorienDrawables() = default;

zappy::Trantorien::Trantorien(std::size_t id) : id(id) {}

zappy::Trantorien::~Trantorien() = default;

void zappy::Trantorien::updateDisplay(zappy::render3d::Camera &camera)
{
    double scaleFromTile = 0.5;

    directionForCam = getDirectionForCam(camera, direction);

    switch (directionForCam)
    {
    case CamDirection::TOWARDS:
        _drawables.body.setTexture(*_drawables.towardsCamera);
        break;
    case CamDirection::AWAY:
        _drawables.body.setTexture(*_drawables.awayFromCamera);
        break;
    case CamDirection::LEFTC:
        _drawables.body.setTexture(*_drawables.left);
        break;
    case CamDirection::RIGHTC:
        _drawables.body.setTexture(*_drawables.right);
        break;
    default:
        _drawables.body.setTexture(*_drawables.towardsCamera);
        break;
    }

    float characterScale = (camera.unitaryPixelsSize * scaleFromTile) / _drawables.body.getTexture()->getSize().x;

    _drawables.body.setOrigin(_drawables.body.getTexture()->getSize().x / 2, _drawables.body.getTexture()->getSize().y);
    _drawables.body.setScale(characterScale, characterScale);
    _drawables.body.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ);
    _drawables.shadow.setRadius(camera.unitaryPixelsSize / 3);
    _drawables.shadow.setOrigin(camera.unitaryPixelsSize / 3, camera.unitaryPixelsSize / 3);
    _drawables.shadow.setScale(1, 0.7);
    _drawables.shadow.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                  camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ);
}

void zappy::Trantorien::setTextures(std::shared_ptr<sf::Texture> &towardsCamera, std::shared_ptr<sf::Texture> &awayFromCamera, std::shared_ptr<sf::Texture> &left,
                                    std::shared_ptr<sf::Texture> &right)
{
    _drawables.towardsCamera = towardsCamera;
    _drawables.awayFromCamera = awayFromCamera;
    _drawables.left = left;
    _drawables.right = right;
}

zappy::CamDirection zappy::Trantorien::getDirectionForCam(zappy::render3d::Camera &camera, short direction)
{
    math::Vector3D cameraDirection = camera.direction;
    std::map<short, sf::Vector2f> directionVectors = {
            {UP, sf::Vector2f(0, -1)},  // Up
            {LEFT, sf::Vector2f(-1, 0)},   // Left
            {DOWN, sf::Vector2f(0, 1)},   // Down
            {RIGHT, sf::Vector2f(1, 0)},   // Right
    };
    cameraDirection.z = 0;

    double angle = math::Vector3D::angle(cameraDirection, math::Vector3D(directionVectors[direction].x, directionVectors[direction].y, 0));

    if (angle >= 135 && angle <= 225)
        return AWAY;
    if (angle >= 45 && angle <= 135)
        return LEFTC;
    if (angle >= 225 && angle <= 315)
        return RIGHTC;

    return TOWARDS;
}

void zappy::Trantorien::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.shadow, states);
}
