/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"

#include "HawkinsComponent.hpp"
//==============================================================================
MainContentComponent::MainContentComponent()
{
    
    setSize (1152, 768);
    HawkinsComponent *hc = new HawkinsComponent();
    addAndMakeVisible(*hc);
    
}

MainContentComponent::~MainContentComponent()
{
    
}
//
void MainContentComponent::paint (Graphics& g)
{
    //background
    g.fillAll (Colour(51,51,51));
    
    
    
}

void MainContentComponent::resized()
{
    
}




