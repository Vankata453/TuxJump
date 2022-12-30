//  TuxJump
//  Copyright (C) 2022 Vankata453
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TUXJUMP_EDITOR_EDITOR_HEADER
#define TUXJUMP_EDITOR_EDITOR_HEADER

#include "game/mode.hpp"
#include "util/current_object.hpp"

class EditorWidget;
class Level;
class Positionf;
class TileMap;

class Editor final : public CurrentObject<Editor>,
                     public GameMode
{
private:
  static const float s_nav_speed;

private:
  std::unique_ptr<Level> m_level;
  std::vector<std::unique_ptr<EditorWidget>> m_widgets;
  std::vector<EditorWidget*> m_reverse_widgets;

  Positionf m_pos;
  int m_selected_tilemap;

  bool m_control_held;

public:
  Editor();
  ~Editor();

  void draw(const RenderContext& context) override;
  void process_event(const SDL_Event& ev) override;

  void check_level_pos();

  // Get widgets
  template<class C>
  C* get_widget()
  {
    for (auto& widget_ptr : m_widgets)
    {
      C* widget = dynamic_cast<C*>(widget_ptr.get());
      if (widget) return widget;
    }
    return nullptr;
  }

  // Get properties
  const Positionf& get_pos() const { return m_pos; }
  TileMap& get_selected_tilemap() const;

private:
  Editor(const Editor&) = delete;
  Editor& operator=(const Editor&) = delete;
};

#endif
