/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent(): Hawkins("../../../../Source/layout.json")
{
    
    setSize (1152, 768);
    ComponentArray = Hawkins.getComponents("Slider");
    TextButtonComponentArray = Hawkins.getComponents("TextButton");
    
    for (auto &child: TextButtonComponentArray)
    {
        TextButton *t = new TextButton();
        
        addAndMakeVisible(t);
        
        t->setButtonText(child["name"]);
        t->setBounds(child["position"]["x"], child["position"]["y"],
                     child["size"]["width"], child["size"]["height"]);
        
        t->addListener(this);
        
        componentMap[child["name"]] = t;
        textButtonArray.add(t);
    }
    
    defaultMapFunctions();
    AnimationPropArray = Hawkins.getAnimations();
    generateComponentAnimators();
}

MainContentComponent::~MainContentComponent()
{
    
}

void MainContentComponent::paint (Graphics& g)
{
    //background
    g.fillAll (Colour(51,51,51));
    Hawkins.renderGraphics(g);
    
}

void MainContentComponent::resized()
{
    for(int i = 0; i < TextButtonComponentArray.size(); i++)
    {
        json child_data = TextButtonComponentArray[i];
        json child_data_position = child_data["position"];
        json child_data_size = child_data["size"];
        textButtonArray[i]->setBounds(child_data_position["x"], child_data_position["y"],
                                      child_data_size["width"], child_data_size["height"]);
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

void MainContentComponent::defaultMapFunctions()
{
    mapFunction("openButtonPressed", [&]{buttonCallbacks::openButtonPressed();});
    mapFunction("anotherButtonPressed", buttonCallbacks::anotherButtonPressed); // map as fn ptr
    mapFunction("helloworld",[&]{MainContentComponent::moveButtonPressed();}); // map as lambda
}



/**
 @brief Maps a string s to a function pointer f.
 
 @param std::string s - String
 @param func f - Function pointer f.
 
 */
void MainContentComponent::mapFunction(std::string s, func f)
{
    hawkinsMap[s] = f;
}

/**
 @brief Maps a string s to a function pointer f.
 
 @param std::string s - String
 @param std::function<void()> f - Function f. Use a lambda. 
 
 */

void MainContentComponent::mapFunction(std::string s, std::function<void()> f)
{
    hawkinsMap[s] = f;
}

void MainContentComponent::sliderValueChanged (Slider* slider)
{
    
}

void MainContentComponent::generateComponentAnimators(){
    for (auto &animators: AnimationPropArray){
        ComponentAnimator *ca = new ComponentAnimator();
        componentAnimatorMap[animators.componentName] = ca;
    }
}

void MainContentComponent::moveButtonPressed()
{
    animatableProperties animators = AnimationPropArray[0];
    Rectangle<int> nRectangle = Rectangle<int>(animators.finalPosition.x, animators.finalPosition.y,
                                               componentMap[animators.componentName]->getWidth(),
                                               componentMap[animators.componentName]->getHeight());
    
    componentAnimatorMap[animators.componentName]->animateComponent(componentMap[animators.componentName],
                                                                    nRectangle, 1.0f,
                                                                    animators.duration, 0, 1.0, 1.0);
}



