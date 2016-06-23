/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <json.hpp>


/**
 Structure to hold attributes to a paintable thing. 
 @param type - type
 @param x - x coordinate
 @param y - y coordinate
 @param width - width
 @param height - height
 @param color - assigned color
 @param text - text
 @param font - font
 */

struct paintAttrs{
    std::string type;
    int x;
    int y;
    int width;
    int height; 
    Colour color;
    std::string text;
    Font font;
};


using json = nlohmann::json;

//std::map<std::string,TextButton> HawkinsTextButton;

class hawkins{
    
public:
    hawkins(std::string); //this is inefficient, right off the bat. But, this is just a proof of concept.
    ~hawkins();
    void parse();
    Array<paintAttrs> getPaintableElements();
    void getComponents();
private:
    enum hawkins_types{
        painted_text,
        drawing_component
    };
    
    std::string str;
    json j;
    bool str_to_json = false;
protected:
    paintAttrs generatePaintTextElement(json);
    paintAttrs generatePaintRectElement(json);
    paintAttrs generatePaintEllipseElement(json);
    
};

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainContentComponent   : public Component
{
    
public:
    //==============================================================================
    
    MainContentComponent();
    ~MainContentComponent();
    
    void paint (Graphics&);
    void resized();
    
private:
    hawkins jsonElements;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
