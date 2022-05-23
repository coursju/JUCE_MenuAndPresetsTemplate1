/*
  ==============================================================================

    CustomLabel.h
    Created: 20 May 2022 10:13:00am
    Author:  dev

  ==============================================================================
*/

#pragma once


class CustomLabel : public juce::Label
{
public:
    CustomLabel(MenuAndPresetTestAudioProcessor& p) : processor(p)
    {
        blankPreset = "Blank preset";
        addMenuItems();

    }
    ~CustomLabel(){}

    void moveBackward()
    {
        if (getText() != blankPreset)
        {
            int index = presetsList.indexOf(getText());

            if (index > 0)
            {
                newPresetSelected(index - 1);
                setText(getList().getReference(index - 1), juce::dontSendNotification);
            }
        }
    }

    void moveForward()
    {
        if (getText() == blankPreset)
        {
            newPresetSelected(0);
            setText(getList().getReference(0), juce::dontSendNotification);
        }
        else
        {
            int index = presetsList.indexOf(getText());

            if (index < getList().size() - 1)
            {
                newPresetSelected(index + 1);
                setText(getList().getReference(index + 1), juce::dontSendNotification);
            }
        }
    }

    void savePreset()
    {
        if (getText() != blankPreset)
        {
            saveToFile(getText().removeCharacters(".xml"));
        }
    }

    void deletePreset()
    {
        if (getText() != blankPreset)
        {
            deleteButtonPressed(getList().indexOf(getText()));
        }
    }

protected:
    void textWasEdited() override
    {
        if ( ! getList().contains(getText()) && getText() != "")
            saveToFile(getText());

        updateAndShowMenu();
        //DBG("text was edited");
    }

    void mouseUp(const juce::MouseEvent &event) override
    {
        updateAndShowMenu();
    }



private:
    MenuAndPresetTestAudioProcessor& processor;
    juce::PopupMenu menu;
    juce::StringArray presetsList;
    juce::String blankPreset;

    void updateAndShowMenu()
    {
        addMenuItems();
        menu.dismissAllActiveMenus();
        menu.showMenuAsync (juce::PopupMenu::Options{}.withTargetComponent (this));
    }

    void addMenuItems()
    {
        presetsList = getList();
        menu.clear();
        for (juce::String str : presetsList)
            menu.addItem (str, [=]{newPresetSelected(str);});
    }

    juce::StringArray getList()
    {
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName() + "/AutoWahPresets";
        juce::StringArray list;
        juce::File file = juce::File(filePath);

        try{
            auto results = file.findChildFiles(juce::File::findFiles, false, "*.xml");

            for (auto result : results)
            {
                list.add(result.getFileName());
            }
            return list;
        }
        catch ( std::exception e) {
            DBG("CustomLabel::getList() failed :"<< e.what());
            throw ;
        }
    }

    void newPresetSelected(juce::String fileName)
    {
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName() + "/AutoWahPresets/" + fileName;
        juce::File file = juce::File(filePath);
        std::unique_ptr<juce::XmlElement> xmlState;

        try{
            auto apvts = processor.getApvts();
            xmlState = juce::XmlDocument::parse(file);

            if (xmlState.get() != nullptr)
                if (xmlState->hasTagName(apvts->state.getType()))
                    apvts->replaceState(juce::ValueTree::fromXml(*xmlState));

            setText(fileName, juce::dontSendNotification);
        }
        catch ( std::exception e) {
            DBG("CustomLabel::newPresetSelected() failed :"<< e.what());
            throw ;
        }
    }

    void saveToFile(juce::String fileName)
    {
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName() + "/AutoWahPresets/" + fileName + ".xml";
        juce::File file = juce::File(filePath);
        std::unique_ptr<juce::XmlElement> xmlState;

        try{
            auto apvts = processor.getApvts();
            auto state = apvts->copyState();
            std::unique_ptr<juce::XmlElement> xml(state.createXml());

            xmlState = state.createXml();

            if (!file.exists()) {
                file.create();
            }
            else {
                file.deleteFile();
            }

            xml.get()->writeTo(file, {});
        }
        catch ( std::exception e) {
            DBG("CustomLabel::saveToFile() failed :"<< e.what());
            throw ;
        }
    }

    void newPresetSelected(int lastRowSelected)
    {
        juce::String fileName = getList()[lastRowSelected];
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName() + "/AutoWahPresets/" + fileName;
        juce::File file = juce::File(filePath);
        std::unique_ptr<juce::XmlElement> xmlState;

        try{
            auto apvts = processor.getApvts();
            xmlState = juce::XmlDocument::parse(file);

            if (xmlState.get() != nullptr)
                if (xmlState->hasTagName(apvts->state.getType()))
                    apvts->replaceState(juce::ValueTree::fromXml(*xmlState));
        }
        catch ( std::exception e) {
            DBG("CustomLabel::newPresetSelected() failed :"<< e.what());
            throw ;
        }
    }

    void deleteButtonPressed(int lastRowSelected)
    {
        juce::String fileName = getList()[lastRowSelected];
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName() + "/AutoWahPresets/" + fileName;
        juce::File file = juce::File(filePath);

        try{
        if (file.exists()) {
            file.deleteFile();
            setText(blankPreset, juce::dontSendNotification);
        }

        }
        catch ( std::exception e) {
            DBG("CustomLabel::newPresetSelected() failed :"<< e.what());
            throw ;
        }
    }
};
