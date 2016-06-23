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
    
    setSize (1152, 768);
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
    //array of paint arrays.
    Array<paintAttrs> arr(jsonElements.getPaintableElements());
    //iterate through array
    for (paintAttrs paintableElement: arr)
    {
        if(paintableElement.type == "text")
        {
            g.setFont(paintableElement.font);
            g.setColour(paintableElement.color);
            g.drawText(paintableElement.text, paintableElement.x,paintableElement.y, paintableElement.width, paintableElement.height, 1, 1);
        }
        if(paintableElement.type == "rect")
        {
            g.setColour(paintableElement.color);
            g.drawRect(paintableElement.x, paintableElement.y, paintableElement.width, paintableElement.height);
        }
        if(paintableElement.type == "ellipse")
        {
            g.setColour(paintableElement.color);
            g.drawEllipse((float) paintableElement.x, (float) paintableElement.y, (float) paintableElement.width, (float)paintableElement.height,1.0);
        }
    }
    
    
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