/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <json.hpp>

struct paintAttrs{
    std::string type;
    //    int position[2] = {};
    //    int size[2] = {};
    int x;
    int y;
    int width;
    int height; 
    Colour color;
    std::string text;
    Font font;
};

using json = nlohmann::json;

class hawkins{
    
public:
    hawkins(std::string); //this is inefficient, right off the bat. But, this is just a proof of concept.
    ~hawkins();
    void parse();
    Array<paintAttrs> getPaintableElements();
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
