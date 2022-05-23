/*
  ==============================================================================

    MenuPopupTest.h
    Created: 19 May 2022 12:31:44pm
    Author:  dev

  ==============================================================================
*/

#pragma once
#include "PresetsViewComponent.h"


class MenuPopupTest : public juce::Component
{
public:
    MenuPopupTest(MenuAndPresetTestAudioProcessor& p) : processor(p), presetsViewComponent(p)
    {
        presetsViewComponent.setSize(400, 300);


        addAndMakeVisible(textButton);
        textButton.setButtonText("menu");

        addMenuItems();

        textButton.onClick = [&]
        {
            menu.showMenuAsync (juce::PopupMenu::Options{}.withTargetComponent (textButton));
        };
    }

    ~MenuPopupTest()
    {

    }

    void paint(juce::Graphics &g) override
    {

    }

    void resized() override
    {
        textButton.setBounds(getLocalBounds());
    }

private:
    MenuAndPresetTestAudioProcessor& processor;

    void addMenuItems()
    {
        //std::function<void()>  test = [this]{displayAlertWindow();};
        menu.addItem ("Manage presets ", [this]{displayPresetsManager();});
        menu.addItem ("Register ", [this]{displayAlertWindow();});
        menu.addItem ("About ", nullptr);
        menu.addItem ("Synopsis ", nullptr);
        menu.addItem ("Manual ", nullptr);
    }

    void displayAlertWindow()
    {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon, "Test", " Bla bla bla");
    }

    void displayPresetsManager()
    {
        juce::DialogWindow::showDialog("Preset", &presetsViewComponent, getParentComponent(), juce::Colours::lightgrey,true);
    }

    PresetsViewComponent presetsViewComponent;

    juce::TextButton textButton;
    juce::PopupMenu menu;
};