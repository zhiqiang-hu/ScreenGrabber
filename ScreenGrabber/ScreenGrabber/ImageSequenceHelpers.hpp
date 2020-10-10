#pragma once

#include <fstream>
#include <iostream>
#include "ConfigVariables.h"


vector<Mat> images;


inline bool ReadImageSequence()
{
  cout << "Opening image sequence file : " << imageSequenceFile << endl << endl;

  ifstream myFile;
  myFile.open(imageSequenceFile);
  if (myFile.is_open() == false)
  {
    cout << "Failed to open image sequence file : " << imageSequenceFile << endl;
    return false;
  }

  while (myFile.eof() == false)
  {
    string strLine;
    getline(myFile, strLine);
    if (strLine.length() == 0 || strLine[0] == kConfigCommentDelim) { continue; }
    strLine = animationDirectory + strLine;

    Mat mat = imread(strLine);
    if (mat.data == nullptr)
    {
      cout << "Failed to open file : " << strLine << endl;
      continue;
    }
    resize(mat, mat, mat.size() / downscaler);

    images.emplace_back(mat);
    cout << "Added to sequence : " << strLine << endl;
  }

  cout << endl;

  if (images.empty())
  {
    std::cout << "Script yielded no keyframes." << imageSequenceFile << endl;
    return false;
  }

  if (animationSteps <= 0)
  {
    cout << "animationSteps specified problematic.\nValue : " << animationSteps << endl;
    cout << "Exiting Program." << endl;
    return false;
  }

  myFile.close();

  return true;
}


//AL.
//TODO
inline void GetNextCompositeImage()
{
}


//AL.
//TODO
inline void RunImageSequence()
{
  //Try and do what mode 0 is doing but instead of grabbing the screen,
  //GetNextCompositeImage based on current/next image and the step.
}