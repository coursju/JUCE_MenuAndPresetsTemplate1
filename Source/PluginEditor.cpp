/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MenuAndPresetTestAudioProcessorEditor::MenuAndPresetTestAudioProcessorEditor (MenuAndPresetTestAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , presetTest(p)
    , sliderAttachment(*p.getApvts(), "gain", slider)
    , menuPopupTest(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(menuPopupTest);
    addAndMakeVisible(presetTest);
    addAndMakeVisible(slider);


}

MenuAndPresetTestAudioProcessorEditor::~MenuAndPresetTestAudioProcessorEditor()
{
}

//==============================================================================
void MenuAndPresetTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MenuAndPresetTestAudioProcessorEditor::resized()
{
    menuPopupTest.setBounds(getWidth() * 0.1f, getHeight() * 0.1, getWidth() * 0.2f, getHeight() * 0.15f);
    presetTest.setBounds(getWidth() * 0.4f, getHeight() * 0.1f, getWidth() * 0.4f, getHeight() * 0.15f);
    slider.setBounds(getWidth() * 0.1f, getHeight() * 0.3f, getWidth() * 0.6f, getHeight() * 0.15f);
}

