//
//  HawkinsComponent.hpp
//  JSONHawkins
//
//  Created by Ashvala Vinay on 6/25/16.
//
//

#ifndef HawkinsComponent_hpp
#define HawkinsComponent_hpp

#include "Hawkins.hpp"
class buttonCallbacks{
    
public:
    buttonCallbacks()
    {
        
    }
    
    virtual ~buttonCallbacks(){
        
    }
    
    virtual void openButtonPressed(){
        
        FileChooser chooser ("Select a Wave file to play...",
                             File::nonexistent,
                             "*.wav");
        std::cout<<"Open Button pressed!" << std::endl;
        if (chooser.browseForFileToOpen())
        {
            File file (chooser.getResult());
            std::cout<<file.getFileName() << " Was selected to be opened!" <<std::endl;
        }
    }
    static void anotherButtonPressed(){
        std::cout << "Hello!" << std::endl;
    }
    virtual void funct(){
        std::cout<< "function? " <<std::endl;
    }
};

class HawkinsComponent   :
public Component,
public buttonCallbacks,
public Button::Listener,
public Slider::Listener
{
    
public:
    //==============================================================================
    
    HawkinsComponent();
    ~HawkinsComponent();
    
    void paint (Graphics&);
    void resized();
    void buttonClicked (Button*);
    void sliderValueChanged (Slider*);
    void moveButtonPressed();
    typedef void(*func)();
    std::map<std::string, std::function<void()>> hawkinsMap;
    std::map<std::string, Component*> componentMap;
    std::map<std::string, ComponentAnimator*> componentAnimatorMap;
    // all the functions
    void defaultMapFunctions();
    void generateComponentAnimators();
    void mapFunction(std::string s, func f);
    void mapFunction(std::string s, std::function<void()> f);
    
    
private:
    
    //hawkins object
    hawkins Hawkins;
    // all the arrays
    Array<json> TextButtonComponentArray;
    Array<json> ComponentArray;
    OwnedArray<Button> textButtonArray;
    OwnedArray<Slider> SliderComponents;
    Array<animatableProperties> AnimationPropArray;
    void (HawkinsComponent::*myFnc)();
    // all the maps
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HawkinsComponent)
};



HawkinsComponent::HawkinsComponent(): Hawkins("../../../../Source/layout.json")
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

HawkinsComponent::~HawkinsComponent()
{
    
}

void HawkinsComponent::paint (Graphics& g)
{
    //background
    g.fillAll (Colour(51,51,51));
    Hawkins.renderGraphics(g);
    
}

void HawkinsComponent::resized()
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

void HawkinsComponent::buttonClicked (Button* button)
{
    int buttonIndex = textButtonArray.indexOf(button);
    if (buttonIndex != -1)
    {
        hawkinsMap[TextButtonComponentArray[buttonIndex]["callback-function"]]();
    }
}

void HawkinsComponent::defaultMapFunctions()
{
    mapFunction("openButtonPressed", [&]{buttonCallbacks::openButtonPressed();});
    mapFunction("anotherButtonPressed", buttonCallbacks::anotherButtonPressed); // map as fn ptr
    mapFunction("helloworld",[&]{HawkinsComponent::moveButtonPressed();}); // map as lambda
}



/**
 @brief Maps a string s to a function pointer f.
 
 @param std::string s - String
 @param func f - Function pointer f.
 
 */
void HawkinsComponent::mapFunction(std::string s, func f)
{
    hawkinsMap[s] = f;
}

/**
 @brief Maps a string s to a function pointer f.
 
 @param std::string s - String
 @param std::function<void()> f - Function f. Use a lambda.
 
 */

void HawkinsComponent::mapFunction(std::string s, std::function<void()> f)
{
    hawkinsMap[s] = f;
}

void HawkinsComponent::sliderValueChanged (Slider* slider)
{
    
}

void HawkinsComponent::generateComponentAnimators(){
    for (auto &animators: AnimationPropArray){
        ComponentAnimator *ca = new ComponentAnimator();
        componentAnimatorMap[animators.componentName] = ca;
    }
}

void HawkinsComponent::moveButtonPressed()
{
    animatableProperties animators = AnimationPropArray[0];
    Rectangle<int> nRectangle = Rectangle<int>(animators.finalPosition.x, animators.finalPosition.y,
                                               componentMap[animators.componentName]->getWidth(),
                                               componentMap[animators.componentName]->getHeight());
    
    componentAnimatorMap[animators.componentName]->animateComponent(componentMap[animators.componentName],
                                                                    nRectangle, 1.0f,
                                                                    animators.duration, 0, 1.0, 1.0);
}

#endif /* HawkinsComponent_hpp */
