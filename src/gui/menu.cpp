#include "gui/menu.hpp"

Menu::Menu() :
  m_items(),
  m_selected_item(0)
{
}

Menu::~Menu()
{
}

void
Menu::draw(RenderContext& context)
{
  const Position menu_pos = get_pos(context.get_size());
  for (int i = 0; i < static_cast<int>(m_items.size()); i++)
  {
    m_items[i]->draw(context, menu_pos.x, menu_pos.y + 40 * (i + 1), i == m_selected_item);
  }
}

void
Menu::process_event(SDL_Event& ev)
{
  if (m_items.empty()) return;

  switch (ev.type)
  {
    case SDL_KEYDOWN:
    {
      switch (ev.key.keysym.sym)
      {
        case SDLK_UP:
          go_up();
          break;
        case SDLK_DOWN:
          go_down();
          break;
        default:
          m_items[m_selected_item]->process_event(ev); // If none of the menu navigation keys are pressed, process the event in the active item.
          break;
      }
    }
  }
}

// Importing items

void
Menu::add_item(const std::string name, const std::function<void ()>& callback)
{
  m_items.push_back(std::make_unique<MenuItem>(name, callback));
}

// Menu actions

void
Menu::go_up()
{
  m_selected_item--;
  if (m_selected_item < 0) m_selected_item = static_cast<int>(m_items.size()) - 1;
}

void
Menu::go_down()
{
  m_selected_item++;
  if (m_selected_item >= static_cast<int>(m_items.size())) m_selected_item = 0;
}
