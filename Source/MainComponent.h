/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "Hawkins.hpp"

class buttonCallbacks
{
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
    static void MoveButtonPressed(){
    }
};

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainContentComponent   : public Component,
public Button::Listener,
public buttonCallbacks,
public Slider::Listener
{
    
public:
    //==============================================================================
    
    MainContentComponent();
    ~MainContentComponent();    
    void paint (Graphics&);
    void resized();
    void buttonClicked (Button*);
    void sliderValueChanged (Slider*);
    void moveButtonPressed();
    
    
    
private:
    
    //hawkins object
    hawkins Hawkins;
    
    // all the arrays
    Array<json> TextButtonComponentArray;
    Array<json> ComponentArray;
    OwnedArray<Button> textButtonArray;
    OwnedArray<Slider> SliderComponents;
    Array<animatableProperties> AnimationPropArray;
    void (MainContentComponent::*myFnc)();
    // all the maps
    typedef void(*func)();
    std::map<std::string, std::function<void()>> hawkinsMap;
    std::map<std::string, Component*> componentMap;
    std::map<std::string, ComponentAnimator*> componentAnimatorMap;
    // all the functions
    void defaultMapFunctions();
    void generateComponentAnimators();
    void mapFunction(std::string s, func f);
    void mapFunction(std::string s, std::function<void()> f);
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
