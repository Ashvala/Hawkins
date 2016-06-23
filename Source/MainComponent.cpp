/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"
#include <fstream>
#include <string>

/*
 
 ALL THE JSON Parsing happens here.
 This will eventually be refactored into a separate file. 
 
 */


/**
 @brief Constructor
 @param jsonSTR - string from JSON file
 */
hawkins::hawkins(std::string url)
{
    std::ifstream t(url);
    std::string content((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
    str = content;
    
}

hawkins::~hawkins(){
    //destructor!
}

/**
 @brief this converts the json file's string to a json object.
 */
void hawkins::parse()
{
    
    j = json::parse(str);
    if (str_to_json == false){
        str_to_json = true;
    }
}
/**
 @brief This function returns paintable elements in the json file.
 
 This function takes the json object that you have and returns an array that contains elements of the "paintAttrs" type. 
 */

Array<paintAttrs> hawkins::getPaintableElements(){
    Array<paintAttrs> arr = {};
    if(str_to_json == false){
        this->parse();
    }
    for (auto &element: j){
        std::string typeOfJSONElement = element["type"];
        if(typeOfJSONElement == "painted_text"){
            arr.add(generatePaintTextElement(element));
        }
        if(typeOfJSONElement == "painted_rect"){
            arr.add(generatePaintRectElement(element));
        }
        if(typeOfJSONElement == "painted_ellipse"){
            arr.add(generatePaintEllipseElement(element));
        }
    }
    return arr;
}

paintAttrs hawkins::generatePaintTextElement(json element){
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
paintAttrs hawkins::generatePaintRectElement(json element){
    paintAttrs paintAttr;
    paintAttr.type = "rect";
    paintAttr.x = element["position"]["x"];
    paintAttr.y = element["position"]["y"];
    paintAttr.width = element["size"]["width"];
    paintAttr.height = element["size"]["height"];
    paintAttr.color = Colour(element["colour"][0],element["colour"][1],element["colour"][2]);
    return paintAttr;
}

paintAttrs hawkins::generatePaintEllipseElement(json element){
    paintAttrs paintAttr;
    paintAttr.type = "ellipse";
    paintAttr.x = element["position"]["x"];
    paintAttr.y = element["position"]["y"];
    paintAttr.width = element["size"]["width"];
    paintAttr.height = element["size"]["height"];
    paintAttr.color = Colour(element["colour"][0],element["colour"][1],element["colour"][2]);
    return paintAttr;
}




//==============================================================================
MainContentComponent::MainContentComponent(): jsonElements("/Users/ashvala/Projects/JSONHawkins/Source/layout.json")
{
    
    setSize (800, 600);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    
    g.fillAll (Colour(51,51,51));
    Array<paintAttrs> arr = jsonElements.getPaintableElements();
    for (paintAttrs paintableElement: arr){
        if(paintableElement.type == "text"){
            g.setFont(paintableElement.font);
            g.setColour(paintableElement.color);
            g.drawText(paintableElement.text, paintableElement.x,paintableElement.y, paintableElement.width, paintableElement.height, 1, 1);
        }
        if(paintableElement.type == "rect"){
            g.setColour(paintableElement.color);
            g.drawRect(paintableElement.x, paintableElement.y, paintableElement.width, paintableElement.height);
        }
        if(paintableElement.type == "ellipse"){
            g.setColour(paintableElement.color);
            g.drawEllipse((float) paintableElement.x, (float) paintableElement.y, (float) paintableElement.width, (float)paintableElement.height,1.0);
        }
    }
    
    
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
