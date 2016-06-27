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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (buttonCallbacks)
};

class HawkinsComponent   :
public Component,
public buttonCallbacks,
public Button::Listener,
public Slider::Listener
{
    
public:
    typedef void(*func)();
    std::map<std::string, std::function<void()>> hawkinsMap;
    std::map<std::string, Component*> componentMap;
    std::map<std::string, ComponentAnimator*> componentAnimatorMap;
    
    //==============================================================================
    
    HawkinsComponent(std::string url): JSON_URL(url){
        Hawkins.setURL(url);
        setSize (1152, 768);
        SliderComponentArray = Hawkins.getComponents("Slider");
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
    ~HawkinsComponent(){
        
    }
    
    void paint (Graphics &g) override{
        //background
        g.fillAll (Colour(51,51,51));
        Hawkins.renderGraphics(g);
    }
    
    void resized() override{
        for(int i = 0; i < TextButtonComponentArray.size(); i++)
        {
            json child_data = TextButtonComponentArray[i];
            json child_data_position = child_data["position"];
            json child_data_size = child_data["size"];
            textButtonArray[i]->setBounds(child_data_position["x"], child_data_position["y"],
                                          child_data_size["width"], child_data_size["height"]);
        }
        
    }
    void buttonClicked (Button* button) override{
        int buttonIndex = textButtonArray.indexOf(button);
        if (buttonIndex != -1)
        {
            hawkinsMap[TextButtonComponentArray[buttonIndex]["callback-function"]]();
        }
        
    }
    
    void sliderValueChanged (Slider* s) override{
        
    }
    
    void moveButtonPressed(){
        animatableProperties animators = AnimationPropArray[0]; //this is the open button! Haha.
        Rectangle<int> nRectangle = Rectangle<int>(animators.finalPosition.x, animators.finalPosition.y,
                                                   componentMap[animators.componentName]->getWidth(),
                                                   componentMap[animators.componentName]->getHeight());
        
        componentAnimatorMap[animators.componentName]->animateComponent(componentMap[animators.componentName],
                                                                        nRectangle, 1.0f,
                                                                        animators.duration, 0, 1.0, 1.0);
        
    }
    
    void openJSON(){
        std::string final_cmd = "open " + JSON_URL;
        std::system(final_cmd.c_str());
    }
    
    void defaultMapFunctions(){
        mapFunction("openButtonPressed", [&]{buttonCallbacks::openButtonPressed();});
        mapFunction("anotherButtonPressed", buttonCallbacks::anotherButtonPressed); // map as fn ptr
        mapFunction("moveOpenButton",[&]{HawkinsComponent::moveButtonPressed();});// map as lambda
        mapFunction("openJSON", [&]{HawkinsComponent::openJSON();});
    }
    
    
    void generateComponentAnimators(){
        for (auto &animators: AnimationPropArray){
            ComponentAnimator *ca = new ComponentAnimator();
            componentAnimatorMap[animators.componentName] = ca;
        }
        
    }
    /**
     @brief Maps a string s to a function pointer f.
     
     @param std::string s - String
     @param func f - Function pointer f.
     
     */
    void mapFunction(std::string s, func f)
    {
        hawkinsMap[s] = f;
    }
    
    
    
    /**
     @brief Maps a string s to a function pointer f.
     
     @param std::string s - String
     @param std::function<void()> f - Function f. Use a lambda.
     
     */
    
    void mapFunction(std::string s, std::function<void()> f)
    {
        hawkinsMap[s] = f;
    }
    
    
private:
    
    //hawkins object
    hawkins Hawkins;
    std::string JSON_URL;
    // all the arrays
    Array<json> TextButtonComponentArray;
    Array<json> SliderComponentArray;
    OwnedArray<Button> textButtonArray;
    OwnedArray<Slider> SliderComponents;
    Array<animatableProperties> AnimationPropArray;
    // all the maps
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HawkinsComponent)
};

#endif /* HawkinsComponent_hpp */
