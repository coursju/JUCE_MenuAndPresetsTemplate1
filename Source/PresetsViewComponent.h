/*
  ==============================================================================

    PresetsViewComponent.h
    Created: 19 May 2022 5:33:04pm
    Author:  dev

  ==============================================================================
*/

#pragma once
#include "PresetsViewListBoxModel.h"


class PresetsViewComponent : public juce::Component
{
public:
    PresetsViewComponent(MenuAndPresetTestAudioProcessor& p)
            : audioProcessor(p)
            , listBox("presets", &presetsViewListBoxModel)
            , presetsViewListBoxModel(p, listBox)
    {
        newButton.setButtonText("new");
        newButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
        newButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);

        saveButton.setButtonText("save");
        saveButton.setColour(juce::TextButton::textColourOffId, juce::Colours::fuchsia);
        saveButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkkhaki);

        newButton.onClick = [this] {newPreset(); };
        saveButton.onClick = [this] {savePreset(); };

        addAndMakeVisible(newButton);
        addAndMakeVisible(saveButton);
        addAndMakeVisible(newLabel);

        newLabel.setEditable(true);
        newLabel.setColour(juce::Label::backgroundColourId, juce::Colours::khaki);
        newLabel.setColour(juce::Label::outlineColourId, juce::Colours::lavender);

        addAndMakeVisible(listBox);
        listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::maroon);
        listBox.updateContent();
    }

    ~PresetsViewComponent()
    {
    }

    void resized() override
    {
        newLabel.setBounds(getWidth() - 170, 10, 160, 30);
        newButton.setBounds(getWidth() - 90, 40, 80, 40);
        saveButton.setBounds(getWidth() - 90, 120, 80, 40);
        listBox.setBounds(10, 10, getWidth() - 200, getHeight() - 20);
    }

    void newPreset()
    {
        if (newLabel.getText() != "")
        {
            presetsViewListBoxModel.saveToFile(newLabel.getText());
            listBox.updateContent();
            newLabel.setText("", juce::dontSendNotification);
        }
    }

    void savePreset()
    {
        presetsViewListBoxModel.saveToFile(listBox.getSelectedRow());
    }

private:
    MenuAndPresetTestAudioProcessor& audioProcessor;
    juce::TextButton newButton, saveButton;
    juce::Label newLabel;
    juce::ListBox listBox;
    PresetsViewListBoxModel presetsViewListBoxModel;
};