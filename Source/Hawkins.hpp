//
//  Hawkins.hpp
//  JSONHawkins
//
//  Created by Ashvala Vinay on 6/25/16.
//
//

#ifndef Hawkins_hpp
#define Hawkins_hpp
#include "../JuceLibraryCode/JuceHeader.h"
#include <json.hpp>
#include <fstream>
#include <string>


using json = nlohmann::json;

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

struct animatableProperties{
    std::string componentName;
    std::string animationType;
    Point<int> finalPosition;
    float duration;
};


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



class hawkins{
    
protected:
    
    paintAttrs generatePaintTextElement(json element)
    {
        paintAttrs paintAttr;
        
        paintAttr.type = "text";
        paintAttr.x = element["position"]["x"];
        paintAttr.y = element["position"]["y"];
        paintAttr.width = element["size"]["width"];
        paintAttr.height = element["size"]["height"];
        paintAttr.text = element["text"];
        paintAttr.color = Colour(element["colour"][0],element["colour"][1],element["colour"][2]);
        paintAttr.font = Font(element["font"], element["font-size"], 0);
        
        return paintAttr;
    }
    
    paintAttrs generatePaintRectElement(json element)
    {
        paintAttrs paintAttr;
        
        paintAttr.type = "rect";
        paintAttr.x = element["position"]["x"];
        paintAttr.y = element["position"]["y"];
        paintAttr.width = element["size"]["width"];
        paintAttr.height = element["size"]["height"];
        paintAttr.color = Colour(element["colour"][0],element["colour"][1],element["colour"][2]);
        
        return paintAttr;
    }
    
    paintAttrs generatePaintEllipseElement(json element)
    {
        paintAttrs paintAttr;
        
        paintAttr.type = "ellipse";
        paintAttr.x = element["position"]["x"];
        paintAttr.y = element["position"]["y"];
        paintAttr.width = element["size"]["width"];
        paintAttr.height = element["size"]["height"];
        paintAttr.color = Colour(element["colour"][0],element["colour"][1],element["colour"][2]);
        
        return paintAttr;
    }
public:
    
    /**
     @brief Constructor
     @param url URL
     */
    hawkins(std::string url)
    {
        std::ifstream t(url);
        std::string content((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());
        str = content;
        this->parse();
    }
    
    virtual ~hawkins()
    {
        //destructor!
        //A clever joke about Shiva being the destroyer of worlds goes here, perhaps?
    }
    
    /**
     @brief this converts the json file's string to a json object.
     */
    void parse()
    {
        
        j = json::parse(str);
        
        if (str_to_json == false)
            str_to_json = true;
        
    }
    
    /**
     @brief This function returns paintable elements in the json file.
     
     This function takes the json object that you have and returns an array that contains elements of the "paintAttrs" type.
     
     @return Array of type "paintAttrs".
     */
    
    Array<paintAttrs> getPaintableElements()
    {
        Array<paintAttrs> arr = {};
        
        for (auto &element: j)
        {
            std::string typeOfJSONElement = element["type"];
            if(typeOfJSONElement == "painted_text")
            {
                arr.add(generatePaintTextElement(element));
            }
            if(typeOfJSONElement == "painted_rect")
            {
                arr.add(generatePaintRectElement(element));
            }
            if(typeOfJSONElement == "painted_ellipse")
            {
                arr.add(generatePaintEllipseElement(element));
            }
        }
        
        return arr;
    }
    
    
    /**
     @brief  This function prints out Text Components
     
     @return Array of type "json"
     */
    
    Array<json> getTextComponents()
    {
        Array<json> TextComponentArray = {};
        Array<json> Components = getComponents();
        for (auto &element: Components)
        {
            std::string typeOfComponent = element["component_type"];
            if(typeOfComponent == "TextButton"){
                TextComponentArray.add(element);
            }
        }
        
        return TextComponentArray;
    }
    Array<json> getSliderComponents()
    {
        Array<json> SliderComponentArray = {};
        Array<json> Components = getComponents();
        for (auto &element: Components)
        {
            std::string typeOfComponent = element["component_type"];
            if(typeOfComponent == "Slider"){
                SliderComponentArray.add(element);
            }
        }
        return SliderComponentArray;
    }
    
    Array<json> getComponents()
    {
        Array<json> ComponentArray = {};
        for (auto &element: j)
        {
            std::string typeOfJSONElement = element["type"];
            if(typeOfJSONElement == "component"){
                ComponentArray.add(element);
            }
        }
        return ComponentArray;
    }
    
    Array<animatableProperties> getAnimations(){
        Array<animatableProperties> AnimationPropArray = {};
        for (auto &element:j)
        {
            std::string type = element["type"];
            if (type == "animated")
            {
                animatableProperties tempStruct;
                tempStruct.componentName = element["component_to_animate"];
                tempStruct.animationType = element["animation_type"];
                if(tempStruct.animationType == "move")
                {
                    // it's either a move
                    tempStruct.finalPosition = Point<int>(element["final_position"][0], element["final_position"][1]);
                    
                }else{
                    // or a fade
                    
                }
                tempStruct.duration = element["duration"];
                AnimationPropArray.add(tempStruct);
            }
        }
        return AnimationPropArray;
        
    }
    void renderGraphics(Graphics &g){
        //array of paint arrays.
        Array<paintAttrs> arr(this->getPaintableElements());
        //iterate through array
        for (paintAttrs paintableElement: arr)
        {
            if(paintableElement.type == "text")
            {
                g.setFont(paintableElement.font);
                g.setColour(paintableElement.color);
                
                g.drawText(paintableElement.text, paintableElement.x,
                           paintableElement.y, paintableElement.width,
                           paintableElement.height, 1, 1);
            }
            if(paintableElement.type == "rect")
            {
                g.setColour(paintableElement.color);
                
                g.drawRect(paintableElement.x, paintableElement.y,
                           paintableElement.width, paintableElement.height);
            }
            if(paintableElement.type == "ellipse")
            {
                g.setColour(paintableElement.color);
                
                g.drawEllipse((float) paintableElement.x, (float) paintableElement.y,
                              (float) paintableElement.width, (float)paintableElement.height,1.0);
                
            }
        }
    }
    
    
    
private:
    
    std::string str;
    json j;
    bool str_to_json = false;
    std::map<std::string, Component*> componentMap;
};



#endif /* Hawkins_hpp */
