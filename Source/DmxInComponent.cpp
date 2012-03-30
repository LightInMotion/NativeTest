/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  29 Mar 2012 4:58:01pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "DmxInComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DmxInComponent::DmxInComponent (BlueLiteX1Mini& blueliteMini_)
    : Thread ("Dmx Input Thread"),
      blueliteMini (blueliteMini_),
      label1 (0),
      label2 (0),
      label3 (0),
      label4 (0),
      label5 (0),
      label6 (0),
      label7 (0),
      label8 (0),
      label9 (0),
      label10 (0),
      label11 (0),
      label12 (0),
      label13 (0),
      label14 (0),
      label15 (0),
      label16 (0),
      label17 (0),
      label18 (0),
      label19 (0),
      label20 (0),
      label21 (0),
      label22 (0),
      label23 (0),
      label24 (0),
      label25 (0),
      label26 (0),
      label27 (0),
      label28 (0),
      label29 (0),
      label30 (0),
      label31 (0),
      label32 (0),
      label33 (0),
      label34 (0),
      label35 (0),
      label36 (0),
      label37 (0),
      label38 (0),
      label39 (0),
      label40 (0),
      label41 (0),
      label42 (0),
      label43 (0),
      label44 (0),
      label45 (0),
      label46 (0),
      label47 (0),
      label48 (0)
{
    addAndMakeVisible (label1 = new Label (L"new label",
                                           L"0"));
    label1->setTooltip (L"Input 1");
    label1->setFont (Font (15.0000f, Font::plain));
    label1->setJustificationType (Justification::centred);
    label1->setEditable (false, false, false);
    label1->setColour (Label::textColourId, Colours::azure);
    label1->setColour (TextEditor::textColourId, Colours::black);
    label1->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"0"));
    label2->setTooltip (L"Input 2");
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::azure);
    label2->setColour (Label::outlineColourId, Colour (0x0));
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label3 = new Label (L"new label",
                                           L"0"));
    label3->setTooltip (L"Input 3");
    label3->setFont (Font (15.0000f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::azure);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label4 = new Label (L"new label",
                                           L"0"));
    label4->setTooltip (L"Input 4");
    label4->setFont (Font (15.0000f, Font::plain));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::azure);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label5 = new Label (L"new label",
                                           L"0"));
    label5->setTooltip (L"Input 5");
    label5->setFont (Font (15.0000f, Font::plain));
    label5->setJustificationType (Justification::centred);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colours::azure);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label6 = new Label (L"new label",
                                           L"0"));
    label6->setTooltip (L"Input 6");
    label6->setFont (Font (15.0000f, Font::plain));
    label6->setJustificationType (Justification::centred);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colours::azure);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label7 = new Label (L"new label",
                                           L"0"));
    label7->setTooltip (L"Input 7");
    label7->setFont (Font (15.0000f, Font::plain));
    label7->setJustificationType (Justification::centred);
    label7->setEditable (false, false, false);
    label7->setColour (Label::textColourId, Colours::azure);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label8 = new Label (L"new label",
                                           L"0"));
    label8->setTooltip (L"Input 8");
    label8->setFont (Font (15.0000f, Font::plain));
    label8->setJustificationType (Justification::centred);
    label8->setEditable (false, false, false);
    label8->setColour (Label::textColourId, Colours::azure);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label9 = new Label (L"new label",
                                           L"0"));
    label9->setTooltip (L"Input 9");
    label9->setFont (Font (15.0000f, Font::plain));
    label9->setJustificationType (Justification::centred);
    label9->setEditable (false, false, false);
    label9->setColour (Label::textColourId, Colours::azure);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label10 = new Label (L"new label",
                                            L"0"));
    label10->setTooltip (L"Input 10");
    label10->setFont (Font (15.0000f, Font::plain));
    label10->setJustificationType (Justification::centred);
    label10->setEditable (false, false, false);
    label10->setColour (Label::textColourId, Colours::azure);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label11 = new Label (L"new label",
                                            L"0"));
    label11->setTooltip (L"Input 11");
    label11->setFont (Font (15.0000f, Font::plain));
    label11->setJustificationType (Justification::centred);
    label11->setEditable (false, false, false);
    label11->setColour (Label::textColourId, Colours::azure);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label12 = new Label (L"new label",
                                            L"0"));
    label12->setTooltip (L"Input 12");
    label12->setFont (Font (15.0000f, Font::plain));
    label12->setJustificationType (Justification::centred);
    label12->setEditable (false, false, false);
    label12->setColour (Label::textColourId, Colours::azure);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label13 = new Label (L"new label",
                                            L"0"));
    label13->setTooltip (L"Input 13");
    label13->setFont (Font (15.0000f, Font::plain));
    label13->setJustificationType (Justification::centred);
    label13->setEditable (false, false, false);
    label13->setColour (Label::textColourId, Colours::azure);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label14 = new Label (L"new label",
                                            L"0"));
    label14->setTooltip (L"Input 14");
    label14->setFont (Font (15.0000f, Font::plain));
    label14->setJustificationType (Justification::centred);
    label14->setEditable (false, false, false);
    label14->setColour (Label::textColourId, Colours::azure);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label15 = new Label (L"new label",
                                            L"0"));
    label15->setTooltip (L"Input 15");
    label15->setFont (Font (15.0000f, Font::plain));
    label15->setJustificationType (Justification::centred);
    label15->setEditable (false, false, false);
    label15->setColour (Label::textColourId, Colours::azure);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label16 = new Label (L"new label",
                                            L"0"));
    label16->setTooltip (L"Input 16");
    label16->setFont (Font (15.0000f, Font::plain));
    label16->setJustificationType (Justification::centred);
    label16->setEditable (false, false, false);
    label16->setColour (Label::textColourId, Colours::azure);
    label16->setColour (TextEditor::textColourId, Colours::black);
    label16->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label17 = new Label (L"new label",
                                            L"0"));
    label17->setTooltip (L"Input 17");
    label17->setFont (Font (15.0000f, Font::plain));
    label17->setJustificationType (Justification::centred);
    label17->setEditable (false, false, false);
    label17->setColour (Label::textColourId, Colours::azure);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label18 = new Label (L"new label",
                                            L"0"));
    label18->setTooltip (L"Input 18");
    label18->setFont (Font (15.0000f, Font::plain));
    label18->setJustificationType (Justification::centred);
    label18->setEditable (false, false, false);
    label18->setColour (Label::textColourId, Colours::azure);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label19 = new Label (L"new label",
                                            L"0"));
    label19->setTooltip (L"Input 19");
    label19->setFont (Font (15.0000f, Font::plain));
    label19->setJustificationType (Justification::centred);
    label19->setEditable (false, false, false);
    label19->setColour (Label::textColourId, Colours::azure);
    label19->setColour (TextEditor::textColourId, Colours::black);
    label19->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label20 = new Label (L"new label",
                                            L"0"));
    label20->setTooltip (L"Input 20");
    label20->setFont (Font (15.0000f, Font::plain));
    label20->setJustificationType (Justification::centred);
    label20->setEditable (false, false, false);
    label20->setColour (Label::textColourId, Colours::azure);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label21 = new Label (L"new label",
                                            L"0"));
    label21->setTooltip (L"Input 21");
    label21->setFont (Font (15.0000f, Font::plain));
    label21->setJustificationType (Justification::centred);
    label21->setEditable (false, false, false);
    label21->setColour (Label::textColourId, Colours::azure);
    label21->setColour (TextEditor::textColourId, Colours::black);
    label21->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label22 = new Label (L"new label",
                                            L"0"));
    label22->setTooltip (L"Input 22");
    label22->setFont (Font (15.0000f, Font::plain));
    label22->setJustificationType (Justification::centred);
    label22->setEditable (false, false, false);
    label22->setColour (Label::textColourId, Colours::azure);
    label22->setColour (TextEditor::textColourId, Colours::black);
    label22->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label23 = new Label (L"new label",
                                            L"0"));
    label23->setTooltip (L"Input 23");
    label23->setFont (Font (15.0000f, Font::plain));
    label23->setJustificationType (Justification::centred);
    label23->setEditable (false, false, false);
    label23->setColour (Label::textColourId, Colours::azure);
    label23->setColour (TextEditor::textColourId, Colours::black);
    label23->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label24 = new Label (L"new label",
                                            L"0"));
    label24->setTooltip (L"Input 24");
    label24->setFont (Font (15.0000f, Font::plain));
    label24->setJustificationType (Justification::centred);
    label24->setEditable (false, false, false);
    label24->setColour (Label::textColourId, Colours::azure);
    label24->setColour (TextEditor::textColourId, Colours::black);
    label24->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label25 = new Label (L"new label",
                                            L"0"));
    label25->setTooltip (L"Input 25");
    label25->setFont (Font (15.0000f, Font::plain));
    label25->setJustificationType (Justification::centred);
    label25->setEditable (false, false, false);
    label25->setColour (Label::textColourId, Colours::azure);
    label25->setColour (TextEditor::textColourId, Colours::black);
    label25->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label26 = new Label (L"new label",
                                            L"0"));
    label26->setTooltip (L"Input 26");
    label26->setFont (Font (15.0000f, Font::plain));
    label26->setJustificationType (Justification::centred);
    label26->setEditable (false, false, false);
    label26->setColour (Label::textColourId, Colours::azure);
    label26->setColour (TextEditor::textColourId, Colours::black);
    label26->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label27 = new Label (L"new label",
                                            L"0"));
    label27->setTooltip (L"Input 27");
    label27->setFont (Font (15.0000f, Font::plain));
    label27->setJustificationType (Justification::centred);
    label27->setEditable (false, false, false);
    label27->setColour (Label::textColourId, Colours::azure);
    label27->setColour (TextEditor::textColourId, Colours::black);
    label27->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label28 = new Label (L"new label",
                                            L"0"));
    label28->setTooltip (L"Input 28");
    label28->setFont (Font (15.0000f, Font::plain));
    label28->setJustificationType (Justification::centred);
    label28->setEditable (false, false, false);
    label28->setColour (Label::textColourId, Colours::azure);
    label28->setColour (TextEditor::textColourId, Colours::black);
    label28->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label29 = new Label (L"new label",
                                            L"0"));
    label29->setTooltip (L"Input 29");
    label29->setFont (Font (15.0000f, Font::plain));
    label29->setJustificationType (Justification::centred);
    label29->setEditable (false, false, false);
    label29->setColour (Label::textColourId, Colours::azure);
    label29->setColour (TextEditor::textColourId, Colours::black);
    label29->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label30 = new Label (L"new label",
                                            L"0"));
    label30->setTooltip (L"Input 30");
    label30->setFont (Font (15.0000f, Font::plain));
    label30->setJustificationType (Justification::centred);
    label30->setEditable (false, false, false);
    label30->setColour (Label::textColourId, Colours::azure);
    label30->setColour (TextEditor::textColourId, Colours::black);
    label30->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label31 = new Label (L"new label",
                                            L"0"));
    label31->setTooltip (L"Input 31");
    label31->setFont (Font (15.0000f, Font::plain));
    label31->setJustificationType (Justification::centred);
    label31->setEditable (false, false, false);
    label31->setColour (Label::textColourId, Colours::azure);
    label31->setColour (TextEditor::textColourId, Colours::black);
    label31->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label32 = new Label (L"new label",
                                            L"0"));
    label32->setTooltip (L"Input 32");
    label32->setFont (Font (15.0000f, Font::plain));
    label32->setJustificationType (Justification::centred);
    label32->setEditable (false, false, false);
    label32->setColour (Label::textColourId, Colours::azure);
    label32->setColour (TextEditor::textColourId, Colours::black);
    label32->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label33 = new Label (L"new label",
                                            L"0"));
    label33->setTooltip (L"Input 33");
    label33->setFont (Font (15.0000f, Font::plain));
    label33->setJustificationType (Justification::centred);
    label33->setEditable (false, false, false);
    label33->setColour (Label::textColourId, Colours::azure);
    label33->setColour (TextEditor::textColourId, Colours::black);
    label33->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label34 = new Label (L"new label",
                                            L"0"));
    label34->setTooltip (L"Input 34");
    label34->setFont (Font (15.0000f, Font::plain));
    label34->setJustificationType (Justification::centred);
    label34->setEditable (false, false, false);
    label34->setColour (Label::textColourId, Colours::azure);
    label34->setColour (TextEditor::textColourId, Colours::black);
    label34->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label35 = new Label (L"new label",
                                            L"0"));
    label35->setTooltip (L"Input 35");
    label35->setFont (Font (15.0000f, Font::plain));
    label35->setJustificationType (Justification::centred);
    label35->setEditable (false, false, false);
    label35->setColour (Label::textColourId, Colours::azure);
    label35->setColour (TextEditor::textColourId, Colours::black);
    label35->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label36 = new Label (L"new label",
                                            L"0"));
    label36->setTooltip (L"Input 36");
    label36->setFont (Font (15.0000f, Font::plain));
    label36->setJustificationType (Justification::centred);
    label36->setEditable (false, false, false);
    label36->setColour (Label::textColourId, Colours::azure);
    label36->setColour (TextEditor::textColourId, Colours::black);
    label36->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label37 = new Label (L"new label",
                                            L"0"));
    label37->setTooltip (L"Input 37");
    label37->setFont (Font (15.0000f, Font::plain));
    label37->setJustificationType (Justification::centred);
    label37->setEditable (false, false, false);
    label37->setColour (Label::textColourId, Colours::azure);
    label37->setColour (TextEditor::textColourId, Colours::black);
    label37->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label38 = new Label (L"new label",
                                            L"0"));
    label38->setTooltip (L"Input 38");
    label38->setFont (Font (15.0000f, Font::plain));
    label38->setJustificationType (Justification::centred);
    label38->setEditable (false, false, false);
    label38->setColour (Label::textColourId, Colours::azure);
    label38->setColour (TextEditor::textColourId, Colours::black);
    label38->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label39 = new Label (L"new label",
                                            L"0"));
    label39->setTooltip (L"Input 39");
    label39->setFont (Font (15.0000f, Font::plain));
    label39->setJustificationType (Justification::centred);
    label39->setEditable (false, false, false);
    label39->setColour (Label::textColourId, Colours::azure);
    label39->setColour (TextEditor::textColourId, Colours::black);
    label39->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label40 = new Label (L"new label",
                                            L"0"));
    label40->setTooltip (L"Input 40");
    label40->setFont (Font (15.0000f, Font::plain));
    label40->setJustificationType (Justification::centred);
    label40->setEditable (false, false, false);
    label40->setColour (Label::textColourId, Colours::azure);
    label40->setColour (TextEditor::textColourId, Colours::black);
    label40->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label41 = new Label (L"new label",
                                            L"0"));
    label41->setTooltip (L"Input 41");
    label41->setFont (Font (15.0000f, Font::plain));
    label41->setJustificationType (Justification::centred);
    label41->setEditable (false, false, false);
    label41->setColour (Label::textColourId, Colours::azure);
    label41->setColour (TextEditor::textColourId, Colours::black);
    label41->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label42 = new Label (L"new label",
                                            L"0"));
    label42->setTooltip (L"Input 42");
    label42->setFont (Font (15.0000f, Font::plain));
    label42->setJustificationType (Justification::centred);
    label42->setEditable (false, false, false);
    label42->setColour (Label::textColourId, Colours::azure);
    label42->setColour (TextEditor::textColourId, Colours::black);
    label42->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label43 = new Label (L"new label",
                                            L"0"));
    label43->setTooltip (L"Input 43");
    label43->setFont (Font (15.0000f, Font::plain));
    label43->setJustificationType (Justification::centred);
    label43->setEditable (false, false, false);
    label43->setColour (Label::textColourId, Colours::azure);
    label43->setColour (TextEditor::textColourId, Colours::black);
    label43->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label44 = new Label (L"new label",
                                            L"0"));
    label44->setTooltip (L"Input 44");
    label44->setFont (Font (15.0000f, Font::plain));
    label44->setJustificationType (Justification::centred);
    label44->setEditable (false, false, false);
    label44->setColour (Label::textColourId, Colours::azure);
    label44->setColour (TextEditor::textColourId, Colours::black);
    label44->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label45 = new Label (L"new label",
                                            L"0"));
    label45->setTooltip (L"Input 45");
    label45->setFont (Font (15.0000f, Font::plain));
    label45->setJustificationType (Justification::centred);
    label45->setEditable (false, false, false);
    label45->setColour (Label::textColourId, Colours::azure);
    label45->setColour (TextEditor::textColourId, Colours::black);
    label45->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label46 = new Label (L"new label",
                                            L"0"));
    label46->setTooltip (L"Input 46");
    label46->setFont (Font (15.0000f, Font::plain));
    label46->setJustificationType (Justification::centred);
    label46->setEditable (false, false, false);
    label46->setColour (Label::textColourId, Colours::azure);
    label46->setColour (TextEditor::textColourId, Colours::black);
    label46->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label47 = new Label (L"new label",
                                            L"0"));
    label47->setTooltip (L"Input 47");
    label47->setFont (Font (15.0000f, Font::plain));
    label47->setJustificationType (Justification::centred);
    label47->setEditable (false, false, false);
    label47->setColour (Label::textColourId, Colours::azure);
    label47->setColour (TextEditor::textColourId, Colours::black);
    label47->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label48 = new Label (L"new label",
                                            L"0"));
    label48->setTooltip (L"Input 48");
    label48->setFont (Font (15.0000f, Font::plain));
    label48->setJustificationType (Justification::centred);
    label48->setEditable (false, false, false);
    label48->setColour (Label::textColourId, Colours::azure);
    label48->setColour (TextEditor::textColourId, Colours::black);
    label48->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    labels.add (label1);
    labels.add (label2);
    labels.add (label3);
    labels.add (label4);
    labels.add (label5);
    labels.add (label6);
    labels.add (label7);
    labels.add (label8);
    labels.add (label9);
    labels.add (label10);
    labels.add (label11);
    labels.add (label12);
    labels.add (label13);
    labels.add (label14);
    labels.add (label15);
    labels.add (label16);
    labels.add (label17);
    labels.add (label18);
    labels.add (label19);
    labels.add (label20);
    labels.add (label21);
    labels.add (label22);
    labels.add (label23);
    labels.add (label24);
    labels.add (label25);
    labels.add (label26);
    labels.add (label27);
    labels.add (label28);
    labels.add (label29);
    labels.add (label30);
    labels.add (label31);
    labels.add (label32);
    labels.add (label33);
    labels.add (label34);
    labels.add (label35);
    labels.add (label36);
    labels.add (label37);
    labels.add (label38);
    labels.add (label39);
    labels.add (label40);
    labels.add (label41);
    labels.add (label42);
    labels.add (label43);
    labels.add (label44);
    labels.add (label45);
    labels.add (label46);
    labels.add (label47);
    labels.add (label48);
    //[/UserPreSize]

    setSize (416, 440);


    //[Constructor] You can add your own custom stuff here..
    inputEvent = new BlueLiteEvent();
    blueliteMini.addInputEvent (inputEvent.getObject());
    startThread();
    //[/Constructor]
}

DmxInComponent::~DmxInComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    labels.clear();
    //[/Destructor_pre]

    deleteAndZero (label1);
    deleteAndZero (label2);
    deleteAndZero (label3);
    deleteAndZero (label4);
    deleteAndZero (label5);
    deleteAndZero (label6);
    deleteAndZero (label7);
    deleteAndZero (label8);
    deleteAndZero (label9);
    deleteAndZero (label10);
    deleteAndZero (label11);
    deleteAndZero (label12);
    deleteAndZero (label13);
    deleteAndZero (label14);
    deleteAndZero (label15);
    deleteAndZero (label16);
    deleteAndZero (label17);
    deleteAndZero (label18);
    deleteAndZero (label19);
    deleteAndZero (label20);
    deleteAndZero (label21);
    deleteAndZero (label22);
    deleteAndZero (label23);
    deleteAndZero (label24);
    deleteAndZero (label25);
    deleteAndZero (label26);
    deleteAndZero (label27);
    deleteAndZero (label28);
    deleteAndZero (label29);
    deleteAndZero (label30);
    deleteAndZero (label31);
    deleteAndZero (label32);
    deleteAndZero (label33);
    deleteAndZero (label34);
    deleteAndZero (label35);
    deleteAndZero (label36);
    deleteAndZero (label37);
    deleteAndZero (label38);
    deleteAndZero (label39);
    deleteAndZero (label40);
    deleteAndZero (label41);
    deleteAndZero (label42);
    deleteAndZero (label43);
    deleteAndZero (label44);
    deleteAndZero (label45);
    deleteAndZero (label46);
    deleteAndZero (label47);
    deleteAndZero (label48);


    //[Destructor]. You can add your own custom destruction code here..
    signalThreadShouldExit();
    blueliteMini.removeInputEvent (inputEvent.getObject());
    inputEvent->signal();
    stopThread (-1);
    
    inputEvent = nullptr;
    //[/Destructor]
}

//==============================================================================
void DmxInComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DmxInComponent::resized()
{
    label1->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.1128f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label2->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.1128f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label3->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.1128f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label4->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.1128f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label5->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.1128f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label6->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.1128f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label7->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.2199f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label8->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.2199f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label9->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.2199f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label10->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.2199f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label11->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.2199f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label12->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.2199f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label13->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.3231f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label14->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.3231f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label15->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.3231f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label16->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.3231f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label17->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.3231f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label18->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.3231f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label19->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.4302f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label20->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.4302f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label21->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.4302f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label22->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.4302f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label23->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.4302f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label24->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.4302f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label25->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.5296f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label26->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.5296f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label27->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.5296f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label28->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.5296f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label29->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.5296f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label30->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.5296f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label31->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.6367f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label32->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.6367f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label33->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.6367f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label34->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.6367f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label35->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.6367f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label36->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.6367f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label37->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.7438f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label38->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.7438f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label39->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.7438f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label40->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.7438f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label41->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.7438f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label42->setBounds (proportionOfWidth (0.8207f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.7438f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label43->setBounds (proportionOfWidth (0.1626f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.8509f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label44->setBounds (proportionOfWidth (0.2958f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.8509f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label45->setBounds (proportionOfWidth (0.4274f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.8509f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label46->setBounds (proportionOfWidth (0.5575f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.8509f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label47->setBounds (proportionOfWidth (0.6891f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.8509f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    label48->setBounds (proportionOfWidth (0.8200f) - ((proportionOfWidth (0.0968f)) / 2), proportionOfHeight (0.8499f) - ((proportionOfHeight (0.0554f)) / 2), proportionOfWidth (0.0968f), proportionOfHeight (0.0554f));
    //[UserResized] Add your own custom resize handling here..
    Font f(label1->getHeight() * .9f, Font::plain);
    
    for (int n = 0; n < 48; ++n)
        labels[n]->setFont (f);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DmxInComponent::run()
{
    int channels = 48;
    if (blueliteMini.dmxInputSize < channels)
        channels = blueliteMini.dmxInputSize;
    
    MemoryBlock last(channels);
    last.fillWith (0);
    
    while (! threadShouldExit())
    {
        inputEvent->wait();
        if (threadShouldExit())
            return;

        MemoryBlock newest = blueliteMini.readDmxInput();

        do 
        {
            const MessageManagerLock mml (Thread::getCurrentThread());
            if (! mml.lockWasGained())
                return;
            
            for (int n = 0; n < channels; ++n)
            {
                if (last[n] != newest[n])
                {
                    uint8 val = (uint8)newest[n];
                    labels[n]->setText (String(val), false);
                    last[n] = newest[n];
                }
            }
            
        } while (0);
        
        // We don't want to update more than 20 Hz
        sleep(50);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DmxInComponent" componentName=""
                 parentClasses="public Component, Thread" constructorParams="BlueLiteX1Mini&amp; blueliteMini_"
                 variableInitialisers="Thread (&quot;Dmx Input Thread&quot;),&#10;blueliteMini (blueliteMini_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="416" initialHeight="440">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="new label" id="15189880f5d76355" memberName="label1" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 11.185%c 9.682% 5.545%"
         tooltip="Input 1" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c31769731f58af07" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 11.185%c 9.682% 5.545%"
         tooltip="Input 2" textCol="fff0ffff" outlineCol="0" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="1cc8f15ab2c52a93" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 11.185%c 9.682% 5.545%"
         tooltip="Input 3" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="7f798d8839959534" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 11.185%c 9.682% 5.545%"
         tooltip="Input 4" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="feaa02471b48585f" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 11.185%c 9.682% 5.545%"
         tooltip="Input 5" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="4c90f163dd3b005e" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 11.185%c 9.682% 5.545%"
         tooltip="Input 6" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="d0ab089596f98d3c" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 22.084%c 9.682% 5.545%"
         tooltip="Input 7" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="e6003883517082c0" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 22.084%c 9.682% 5.545%"
         tooltip="Input 8" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="52b8f1d361cc3acf" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 22.084%c 9.682% 5.545%"
         tooltip="Input 9" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="18d7e1ff248cb6fc" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 22.084%c 9.682% 5.545%"
         tooltip="Input 10" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="be035bdfb2600cb5" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 22.084%c 9.682% 5.545%"
         tooltip="Input 11" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9373bdb994907d3b" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 22.084%c 9.682% 5.545%"
         tooltip="Input 12" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="5d38c72f1c437e8d" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 32.409%c 9.682% 5.545%"
         tooltip="Input 13" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="4262175e6d7eccd5" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 32.409%c 9.682% 5.545%"
         tooltip="Input 14" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="80156c89a2915f28" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 32.409%c 9.682% 5.545%"
         tooltip="Input 15" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="e79837a03a082a65" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 32.409%c 9.682% 5.545%"
         tooltip="Input 16" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="dd5028d8e3ca8557" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 32.409%c 9.682% 5.545%"
         tooltip="Input 17" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="5e16fbd6fa0895dd" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 32.409%c 9.682% 5.545%"
         tooltip="Input 18" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="15d00f18b383af47" memberName="label19" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 42.925%c 9.682% 5.545%"
         tooltip="Input 19" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="e83d969e06c0028e" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 42.925%c 9.682% 5.545%"
         tooltip="Input 20" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="505c526e7e461aa3" memberName="label21" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 42.925%c 9.682% 5.545%"
         tooltip="Input 21" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="3d1006bbc067a4b7" memberName="label22" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 42.925%c 9.682% 5.545%"
         tooltip="Input 22" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="d25a571cb2345b2" memberName="label23" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 42.925%c 9.682% 5.545%"
         tooltip="Input 23" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="5ebc856772cde35c" memberName="label24" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 42.925%c 9.682% 5.545%"
         tooltip="Input 24" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="4d268d0dfc4d0d4a" memberName="label25" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 53.059%c 9.682% 5.545%"
         tooltip="Input 25" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8af8955b3fd9ba88" memberName="label26" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 53.059%c 9.682% 5.545%"
         tooltip="Input 26" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="18da33ded767155c" memberName="label27" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 53.059%c 9.682% 5.545%"
         tooltip="Input 27" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="3705a794f5997ea3" memberName="label28" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 53.059%c 9.682% 5.545%"
         tooltip="Input 28" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="3edebbd39c807c32" memberName="label29" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 53.059%c 9.682% 5.545%"
         tooltip="Input 29" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="dab89528797af782" memberName="label30" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 53.059%c 9.682% 5.545%"
         tooltip="Input 30" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="81d39ef3d2f3a121" memberName="label31" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 63.576%c 9.682% 5.545%"
         tooltip="Input 31" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="7a081ee787141aed" memberName="label32" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 63.576%c 9.682% 5.545%"
         tooltip="Input 32" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="d41b9bd15453ae69" memberName="label33" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 63.576%c 9.682% 5.545%"
         tooltip="Input 33" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="73c7c74d4c6b49ab" memberName="label34" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 63.576%c 9.682% 5.545%"
         tooltip="Input 34" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="610d86587e7594ad" memberName="label35" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 63.576%c 9.682% 5.545%"
         tooltip="Input 35" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="48551ae324f8fa13" memberName="label36" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 63.576%c 9.682% 5.545%"
         tooltip="Input 36" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="445ae0caff48c99f" memberName="label37" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 74.474%c 9.682% 5.545%"
         tooltip="Input 37" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="6269ae5c080f7e3" memberName="label38" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 74.474%c 9.682% 5.545%"
         tooltip="Input 38" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="f35881063ff0bdfa" memberName="label39" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 74.474%c 9.682% 5.545%"
         tooltip="Input 39" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="188c2e24da9f4d4f" memberName="label40" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 74.474%c 9.682% 5.545%"
         tooltip="Input 40" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="33d5c609a62b3eb5" memberName="label41" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 74.474%c 9.682% 5.545%"
         tooltip="Input 41" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="cf8b3c2e1112295d" memberName="label42" virtualName=""
         explicitFocusOrder="0" pos="82.148%c 74.474%c 9.682% 5.545%"
         tooltip="Input 42" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ebf321b6cb1f3575" memberName="label43" virtualName=""
         explicitFocusOrder="0" pos="16.188%c 84.99%c 9.682% 5.545%" tooltip="Input 43"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="79bed6ab2d8b576f" memberName="label44" virtualName=""
         explicitFocusOrder="0" pos="29.501%c 84.99%c 9.682% 5.545%" tooltip="Input 44"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="5630fad9d8727c42" memberName="label45" virtualName=""
         explicitFocusOrder="0" pos="42.663%c 84.99%c 9.682% 5.545%" tooltip="Input 45"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="e4c6950921691c21" memberName="label46" virtualName=""
         explicitFocusOrder="0" pos="55.825%c 84.99%c 9.682% 5.545%" tooltip="Input 46"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b0fc2b69df3cb87d" memberName="label47" virtualName=""
         explicitFocusOrder="0" pos="68.986%c 84.99%c 9.682% 5.545%" tooltip="Input 47"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="455065bd75f8b55" memberName="label48" virtualName=""
         explicitFocusOrder="0" pos="81.997%c 84.99%c 9.682% 5.545%" tooltip="Input 48"
         textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
