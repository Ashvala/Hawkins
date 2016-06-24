/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent(): jsonElements("../../../../Source/layout.json")
{
    
    setSize (1152, 720);
    TextButtonComponentArray = jsonElements.getTextComponents();
    for (auto &child: TextButtonComponentArray)
    {
        TextButton *t = new TextButton();
        
        addAndMakeVisible(t);
        
        t->setButtonText(child["name"]);
        t->setTopLeftPosition(child["position"]["x"], child["position"]["y"]);
        t->setBounds(child["position"]["x"], child["position"]["y"], child["size"]["width"], child["size"]["height"]);
        t->addListener(this);
        textButtonArray.add(t);
        
    }
    autoMapFunctionsFromJSON();
}

MainContentComponent::~MainContentComponent()
{
    
}

void MainContentComponent::paint (Graphics& g)
{
    //background
    g.fillAll (Colour(51,51,51));
    jsonElements.renderGraphics(g);
    
}

void MainContentComponent::resized()
{
    for(int i = 0; i < TextButtonComponentArray.size(); i++)
    {
        json child_data = TextButtonComponentArray[i];
        json child_data_position = child_data["position"];
        json child_data_size = child_data["size"];
        textButtonArray[i]->setBounds(child_data_position["x"], child_data_position["y"], child_data_size["width"], child_data_size["height"]);
    }
    
}

void MainContentComponent::buttonClicked (Button* button)
{
    int buttonIndex = textButtonArray.indexOf(button);
    if (buttonIndex != -1)
    {
        hawkinsMap[TextButtonComponentArray[buttonIndex]["callback-function"]]();
    }
}

void MainContentComponent::autoMapFunctionsFromJSON()
{
    mapFunction("openButtonPressed", buttonCallbacks::openButtonPressed);
    mapFunction("anotherButtonPressed", buttonCallbacks::anotherButtonPressed);
}
void MainContentComponent::mapFunction(std::string s, func f)
{
    hawkinsMap[s] = f;
}



