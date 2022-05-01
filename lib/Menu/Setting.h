#pragma once
#include <MenuComponent.h>
template <typename T>
struct NamedValue {
    const char* name;
    T value;
};

template <typename T>
class Setting {
    NamedValue<T> m_value;
    bool m_isSet;

   public:
    Setting(NamedValue<T> value) : m_value(value){};
};

template <typename T, int size>
class SettingGroup {
    NamedValue<T> m_options[size];
    int m_selectedOption = 0;

   public:
    SettingGroup(NamedValue<T> options[size]) : m_options(options){};
    SettingGroup(const char* values[size]) {
        for (int i = 0; i < size; i++) {
            m_options[i] = NamedValue<int>{values[i], i};
        }
    };

    typedef void (SettingGroup<T, size>::*setting_func)(int);

    void selectOption(int index) {
        m_selectedOption = index;
    }

    T getSelectedValue() {
        return m_options[m_selectedOption].value;
    }

    SubMenu* createSettingsMenu() {
        SubMenu* menu = new SubMenu("BaseNote");
        for (int i = 0; i < size; i++) {
            menu->addChild(new Leaf(m_options[i].name, [this, i]() { selectOption(i); }));
        }
        return menu;
    }
};