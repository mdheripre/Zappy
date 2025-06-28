/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRenderer.cpp
*/

#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include "Game/Renderer/Sound/ISound.hpp"
#include "Tools/Error/Error.hpp"

namespace sfml
{
    class SFMLSound : public render::ISound
    {
        public:
            SFMLSound(const sf::SoundBuffer &buffer);
            ~SFMLSound();
            void play(bool loop);
            void pause();
            void changeState();
            void stop();
            void reset();
        private:
            bool _paused = false;
            sf::Sound _sound;
    };
} // namespace sfml
