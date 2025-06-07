/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

/**
 * @brief Constructs an empty tile.
 *
 * Initializes all resources on the tile to zero.
 */
gui::Tile::Tile()
{
    for (auto &i : _resources)
    i = 0;
}

/**
 * @brief Removes one unit of the specified resource from the tile.
 *
 * Decrements the count for the specified resource if available.
 *
 * @param res The resource to remove.
 * @return true if the resource was successfully removed, false otherwise.
 */
bool gui::Tile::popResource(Resource res)
{
    int index = static_cast<int>(res);

    if (_resources[index] > 0) {
        _resources[index]--;
        _total--;
        return true;
    }
    return false;
}

/**
 * @brief Adds one unit of the specified resource to the tile.
 *
 * Increments both the resource count and the total resource count.
 *
 * @param res The resource to add.
 */
void gui::Tile::pushResource(Resource res)
{
    int index = static_cast<int>(res);

    _resources[index]++;
    _total++;
}

/**
 * @brief Sets the entire resource array of the tile.
 *
 * Replaces the resource distribution and updates the total resource count accordingly.
 *
 * @param resources An array containing the quantity of each resource (size must be 7).
 */
void gui::Tile::setResources(std::array<int, 7> resources)
{
    int count = 0;

    for (int i = 0; i < 7; i++)
        count += resources[i];
    _total = count;
    _resources = resources;
}
