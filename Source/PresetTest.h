/*
  ==============================================================================

    PresetTest.h
    Created: 19 May 2022 12:41:46pm
    Author:  dev

  ==============================================================================
*/

#pragma once
#include "CustomLabel.h"

class PresetTest : public juce::Component
{
public:
    PresetTest(MenuAndPresetTestAudioProcessor& p) : processor(p), label(p)
    {
        addAndMakeVisible(rewindButton);
        addAndMakeVisible(forwardButton);
        addAndMakeVisible(saveButton);
        addAndMakeVisible(deleteButton);
        addAndMakeVisible(label);

        rewindButton.setButtonText("<");
        forwardButton.setButtonText(">");
        saveButton.setButtonText("S");
        deleteButton.setButtonText("D");

        label.setText("Blank preset", juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        label.setEditable(false, true);

        //Onclick
        rewindButton.onClick = [this]{label.moveBackward();};
        forwardButton.onClick = [this]{label.moveForward();};
        saveButton.onClick = [this]{label.savePreset();};
        deleteButton.onClick = [this]{label.deletePreset();};
    }

    ~PresetTest()
    {

    }

    void paint(juce::Graphics &g) override
    {

    }

    void resized() override
    {
        rewindButton.setBounds(0, 0, getWidth() * 0.1f, getHeight());
        label.setBounds(getWidth() * 0.1f, 0, getWidth() * 0.7f, getHeight());
        forwardButton.setBounds(getWidth() * 0.8, 0, getWidth() * 0.1f, getHeight());
        saveButton.setBounds(getWidth() * 0.9, 0, getWidth() * 0.05f, getHeight());
        deleteButton.setBounds(getWidth() * 0.95, 0, getWidth() * 0.05f, getHeight());

    }

private:
    MenuAndPresetTestAudioProcessor& processor;
    juce::TextButton rewindButton, forwardButton, saveButton, deleteButton;
    CustomLabel label;
};