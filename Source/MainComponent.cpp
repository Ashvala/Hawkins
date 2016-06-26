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
    HawkinsComponent *hc = new HawkinsComponent("../../../../Source/layout.json");
    addAndMakeVisible(*hc);
    
}

MainContentComponent::~MainContentComponent()
{
    
}

void MainContentComponent::paint (Graphics& g)
{    
}

void MainContentComponent::resized()
{
    
}
