//============================================================================
// Name        : gpif001.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <iomanip>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "ZiegVersion.h"

namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;
namespace zv = ZiegVersion;
using namespace std;

typedef vector<string> TStrVect;
typedef TStrVect::const_iterator TStrVectCItr;

enum CmdLineOpts
{
   kVersion,
   kHelp,
   kData,
   kFormat,
   kCanvas,
   kDxf,
   kGif,
   kJpeg,
   kPng,
   kPostscript,
   kSvg,
};

const string kEndStrFormats("END");
const string kPNGFormatStr("png");
const string kFormats[][2]=
{
      {"canvas", "html"},
      {"dxf", "dxf"},
      {"gif", "gif"},
      {"jpeg", "jpg"},
      {"jpg", "jpg"},
      {kPNGFormatStr, kPNGFormatStr},
      {"postscript", "eps"},
      {"eps", "eps"},
      {"svg", "svg"},
      {kEndStrFormats, kEndStrFormats},
};

bool ExtractFormatStr(const string& cmdOptStr, string& fmtNameStr)
{
   size_t cnt(0);
   while(0 != kFormats[cnt][0].compare(kEndStrFormats))
   {
      if(0 == kFormats[cnt][0].compare(cmdOptStr))
      {
         fmtNameStr = kFormats[cnt][1];
         return true;
      }
      ++cnt;
   }
   return false;
}

bool CreateOutputFileNameStr(const string& fmtStr, string& outFileStr)
{
   size_t cnt(0);
   while(0 != kFormats[cnt][0].compare(kEndStrFormats))
   {
      if(0 == kFormats[cnt][0].compare(fmtStr))
      {
         int fileCnt(0);
         do
         {
            stringstream strm;
            strm << "gnuplot_" << setfill('0') << setw(3) << fileCnt << "."
                  << kFormats[cnt][1];
            outFileStr = strm.str();
            ++fileCnt;
         } while (bfs::exists(outFileStr));
         return true;
      }
      ++cnt;
   }
   return false;
}

void ParseCmdLineOpts(const bpo::options_description& cmdline_options,
      const bpo::variables_map& vm)
{
   if (vm.count("help")) {
      cout << cmdline_options << endl;
      cout << "kFormats size = " << sizeof(kFormats[0]) << endl;
      exit(0);
   }
   if (vm.count("version"))
   {
      cout << "GNUPlotInterface (gpif) Program" << endl;
      cout << "Version: " << zv::GetFullVersionString() << endl;
      cout << "  Built: " << zv::BuildDate << "@" << zv::BuildTime << endl;
      cout << "   UUID: " << zv::UUID << endl;
      exit(0);
   }
   int width(600);
   int height(400);
   if (vm.count("width"))
   {
      if (0 == vm.count("dxf"))
      {
         width = vm["width"].as<int>();
         height =
               (0 == vm.count("height") ? width * 3 / 4 : vm["height"].as<int>());
      }
      else
      {
         cout << "DXF format current only supports 120x80 output." << endl;
      }
   }
   string inFileStr;
   if (vm.count("data"))
   {
      inFileStr = vm["data"].as<string>();
      if(!bfs::exists(inFileStr))
      {
         cout << "The input file " << inFileStr << " does not exist." << endl;
         exit(2);
      }
   }
   else
   {
      cout << "You must specify an input file with the '-d' option" << endl;
      exit(3);
   }
   int numColumns(1);
   if (vm.count("columns"))
   {
      numColumns = vm["columns"].as<int>();
   }
   string delimChr(" ");
   if (vm.count("delimiter"))
   {
      delimChr = vm["delimiter"].as<string>();
   }

   TStrVect formatVect;
   string tmpFmtNameStr;
   if (vm.count("format"))
   {
      cout << "Checking format" << endl;
      if(ExtractFormatStr(vm["format"].as<string>(), tmpFmtNameStr))
      {
         formatVect.push_back(tmpFmtNameStr);
      }
      else
      {
         cout << "Format argument (" << vm["format"].as<string>()
               << ") is not a valid type" << endl;
         cout << "Run this program with the -h option to see all valid options"
               << endl;
         exit(1);
      }
   }
   size_t cnt(0);
   while(0 != kFormats[cnt][0].compare(kEndStrFormats))
   {
      if(vm.count(kFormats[cnt][0]))
      {
         formatVect.push_back(kFormats[cnt][0]);
      }
      ++cnt;
   }
   if(0 == formatVect.size())
   {
      formatVect.push_back(kPNGFormatStr);
   }
   cout << "Format" << (1 < formatVect.size() ? "s: " : ": ") << endl;
   for(auto itr = formatVect.begin(); formatVect.end() != itr; ++itr)
   {
      string outFileStr;
      if(CreateOutputFileNameStr(*itr, outFileStr))
      {
         cout << "  " << (*itr) << " " << outFileStr << endl;
         string cmdStr("gnuplot -e \"set term ");
         cmdStr.append(*itr);
         if(0 != (*itr).compare("dxf"))
         {
            stringstream dimStrm;
            dimStrm << " size " << width << ", " << height;
            cmdStr.append(dimStrm.str());
         }
         cmdStr.append("; set output \\\"");
         cmdStr.append(outFileStr);
         cmdStr.append("\\\";");
         if(vm.count("grid"))
         {
            cmdStr.append("set grid;");
         }
         if (vm.count("delimiter"))
         {
            cmdStr.append("set datafile separator \\\"");
            cmdStr.append(delimChr);
            cmdStr.append("\\\";");
         }
         cmdStr.append("plot \\\"");
//
         cmdStr.append(inFileStr);
         if(1 == numColumns)
         {
            cmdStr.append("\\\" with lines\"");
         }
         else
         {
            cmdStr.append("\\\" using 1");
            for(int i=2; i<=numColumns; ++i)
            {
               stringstream strm;
               strm << ":" << i;
               cmdStr.append(strm.str());
            }
            cmdStr.append(" with lines\"");
         }
         cout << "Command: [" << cmdStr << "]" << endl;
         ::system(cmdStr.c_str());
      }
   }

}

// TODO Convert GPS time-in-week to value gnuplot understands

int main(int ac, char* av[]) {
   try
   {
      bpo::options_description cmdline_options;
      cmdline_options.add_options()
         ("version,v", "print version string")
         ("help,h", "produce help message")
         ("data,d", bpo::value<string>(), "Input data file (required)")
         ("columns,c", bpo::value<int>(), "Number of columns in input data "
               "file")
         ("delimiter", bpo::value<string>(), "Column separator in input data "
               "file")
         ("format,f", bpo::value<string>(), "Output file format (default is "
               "PNG)")
         ("width,w", bpo::value<int>(), "Output image width (default is 4:3 "
               "ratio). The image will normally be 600 x 400 if no width is "
               "specified.")
         ("height,g", bpo::value<int>(), "Output image height (width must be "
               "set)")
         ("canvas", "Output in HTML format")
         ("dxf", "Output in DXF format (default size 120x80)")
         ("gif", "Output in GIF format")
         ("jpeg", "Output in JPEG format (uses libgd and TrueType fonts)")
         ("png", "Output in PNG images (uses libgd and TrueType fonts)")
         ("postscript", "Output in PostScript format")
         ("svg", "Output in SVG format")
         ("grid", "Show grid in plot")
      ;
      bpo::variables_map vm;
      bpo::store(bpo::parse_command_line(ac, av, cmdline_options), vm);
      bpo::notify(vm);
      ParseCmdLineOpts(cmdline_options, vm);
   }
   catch(exception& e)
   {
      cout << "Exception thrown: " << e.what() << endl;
   }
   catch(...)
   {
      cout << "Unknown exception thrown" << endl;
   }
	return 0;
}
