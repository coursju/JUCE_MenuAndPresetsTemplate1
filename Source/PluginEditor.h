/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MenuPopupTest.h"
#include "PresetTest.h"


//==============================================================================
/**
*/
class MenuAndPresetTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MenuAndPresetTestAudioProcessorEditor (MenuAndPresetTestAudioProcessor&);
    ~MenuAndPresetTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MenuAndPresetTestAudioProcessor& audioProcessor;

    juce::Slider slider;
    juce::AudioProcessorValueTreeState::SliderAttachment sliderAttachment;

    MenuPopupTest menuPopupTest;
    PresetTest presetTest;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuAndPresetTestAudioProcessorEditor)
};
