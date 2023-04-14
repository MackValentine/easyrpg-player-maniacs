/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include "spriteset_battle.h"
#include "cache.h"
#include "game_actors.h"
#include "game_battle.h"
#include "game_battler.h"
#include "game_enemy.h"
#include "game_enemyparty.h"
#include "game_party.h"
#include "game_screen.h"
#include "main_data.h"
#include "player.h"
#include "sprite_battler.h"
#include "sprite_actor.h"
#include "sprite_enemy.h"

#include "output.h"

Spriteset_Battle::Spriteset_Battle(const std::string bg_name, int terrain_id)
{
	background_name = std::move(bg_name);

	// Create background
	if (!background_name.empty()) {
		background.reset(new Background(background_name));
	} else {
		// Background verifies that the Terrain ID is valid
		background.reset(new Background(terrain_id));
	}
	Game_Battle::ChangeBackground(background_name);

	// Create the sprites
	std::vector<Game_Battler*> battler;
	Main_Data::game_enemyparty->GetBattlers(battler);
	if (Player::IsRPG2k3()) {
		for (unsigned int i = 0; i < lcf::Data::actors.size(); ++i) {
			battler.push_back(Main_Data::game_actors->GetActor(i + 1));
		}
	}

	timer1.reset(new Sprite_Timer(0));
	timer2.reset(new Sprite_Timer(1));

	screen.reset(new Screen());
}

void Spriteset_Battle::Update() {
	Tone new_tone = Main_Data::game_screen->GetTone();

	// Handle background change
	const auto& current_bg = Game_Battle::GetBackground();
	if (background_name != current_bg) {
		background_name = current_bg;
		if (!background_name.empty()) {
			background.reset(new Background(background_name));
		} else {
			background.reset();
		}
	}
	background->SetTone(new_tone);
	background->Update();


	if (zoomTimer >= 0) {

		double z = (destZoom + (startZoom - destZoom) * (zoomTimer / 15.0)) / 100.0;

		zoomX = z;
		zoomY = z;

		int zx;
		int zy;
		zx = lerp(zoomPosX, destZoomX, 1.0 / 15.0);
		zy = lerp(zoomPosY, destZoomY, 1.0 / 15.0);

		int dx = Player::Screen_Width / 2;
		int dy = Player::Screen_Height / 2;

		int minX = -(Player::Screen_Width / 2 * zoomX - Player::Screen_Width / 2) + dx - 4 * (1.0-z);
		int minY = -(Player::Screen_Height / 2 * zoomY - Player::Screen_Height / 2) + dy - 4 * (1.0-z);
		int maxX = Player::Screen_Width / 2 * zoomX - Player::Screen_Width / 2 + dx + 4 * (1.0-z);
		int maxY = Player::Screen_Height / 2 * zoomY - Player::Screen_Height / 2 + dy + 4 *(1.0-z);


		zx = std::max(zx, minX);
		zy = std::max(zy, minY);

		zx = std::min(zx, maxX);
		zy = std::min(zy, maxY);

		zoomPosX = zx;
		zoomPosY = zy;

		zoomTimer--;

	}

}

float Spriteset_Battle::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
