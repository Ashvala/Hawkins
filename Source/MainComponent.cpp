/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"



// The fun part begins here-ish.


//==============================================================================
MainContentComponent::MainContentComponent(): jsonElements("/Users/ashvala/Projects/JSONHawkins/Source/layout.json")
{
    
    setSize (1152, 720);
    ComponentArray = jsonElements.getTextComponents();
    for (auto &child: ComponentArray){
        std::cout<<child<<std::endl;
        TextButton *t = new TextButton();
        addAndMakeVisible(t);
        t->setButtonText(child["name"]);
        t->setTopLeftPosition(child["position"]["x"], child["position"]["y"]);
        t->setBounds(child["position"]["x"], child["position"]["y"], child["size"]["width"], child["size"]["height"]);
        t->addListener(this);
        textButtonArray.add(t);
    }
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
    for(int i = 0; i < ComponentArray.size(); i++)
    {
        json child_data = ComponentArray[i];
        textButtonArray[i]->setBounds(child_data["position"]["x"], child_data["position"]["y"], child_data["size"]["width"], child_data["size"]["height"]);
    }
    
}
void MainContentComponent::buttonClicked (Button* button)
{
    int buttonIndex = textButtonArray.indexOf(button);
    if (buttonIndex != -1)
    {
        std::cout << "button pressed! "<< textButtonArray.indexOf(button) << std::endl;
        std::cout << "associated json for button: " << ComponentArray[buttonIndex] << std::endl;
    }
}