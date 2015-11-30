//============================================================================
// Name        : gpif001.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
gnuplot --jhelp
aptitude search gnuplot
sudo apt-get install gnuplotsudo apt-get install
sudo apt-get install gnuplot
sudo apt-get install gnuplot
gnuplot --help
aptitude search gnuplot
sudo apt-get install gnuplot
gnuplot --help
gnuplot
gnuplot --help
gnuplot -h
gnuplot -V
gnuplot -persist -e "set title ’Sine curve’; plot sin(x)"
gnuplot -persist -e "set title `Sine curve`; plot sin(x)"
gnuplot
gnuplot -persist -e "set title ’Sine curve’; plot sin(x)"
gnuplot -persist -e "set title `Sine curve`; plot sin(x)"
gnuplot -persist -e "plot sin(x)"
gnuplot -persist -e "set title \"Sine curve\"; plot sin(x)"
gnuplot -persist -e "set title \"Sine curve\"; plot sin(x)" sin.png
gnuplot -h
gnuplot -d
gnuplot -persist -e "set title \"Sine curve\"; plot sin(x)" > sin.png
gnuplot -persist -e "set title \"Sine curve\"; plot sin(x)" > sin.plt
gnuplot sin.dat
gnuplot
gnuplot
gnuplot -persist -e ’plot [-5:5] sinh(x)’
gnuplot -persist -e "plot [-5:5] sinh(x)"
gnuplot -persist -e "plot [-5:5] sinh(x)" > sinh.png
gnuplot -persist -e
gnuplot
gnuplot
gnuplot terminal
gnuplot -e terminal
gnuplot
gnuplot -e set terminal
gnuplot -e "set terminal"
gnuplot
gnuplot
sudo find / -name gnuplotrc.
sudo find / -name gnuplotrc
gnuplot
history | grep gnuplot
gnuplot -e "set term png size 600, 400; set output "data1.png"; plot "sin1.dat" with lines"
gnuplot -e "set term png size 600, 400; set output \"data1.png\"; plot "sin1.dat" with lines"
gnuplot -e "set term png size 600, 400; set output \"data1.png\"; plot \"sin1.dat\" with lines"
gnuplot -e "set term png size 600, 400; set output \"gpif.png\"; plot \"sin.dat\" with lines"
gnuplot -e "set term png size 600, 400; set output "gpif.png"; plot "sin.dat" with lines"
gnuplot -e "set term png size 600, 400; set output \"gpif.png\"; plot "sin.dat" with lines"
gnuplot -e "set term png size 600, 400; set output \"data1.png\"; plot \"sin1.dat\" with lines"
gnuplot
gnuplot
gnuplot -e "set term jpg size 600, 400; set output \"gpif000.jpg\"; plot \"sin1.dat\" with lines"
gnuplot -e "set term jpeg size 600, 400; set output \"gpif000.jpg\"; plot \"sin1.dat\" with lines"
gnuplot -e "set term jpeg size 600, 400; set output \"gpif000.jpg\"; plot \"sin1.dat\" with lines"
history | grep gnuplot
*/

#include <iostream>
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

void ExecuteOptions()
{

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
      cout << "  " << (*itr) << endl;
//gnuplot -e "set term png size 600, 400; set output "data1.png"; plot "sin1.dat" with lines"
//gnuplot -e "set term png size 600, 400; set output \"data1.png\"; plot \"sin_1D.dat\" with lines"
      string cmdStr("gnuplot -e \"set term ");
      cmdStr.append(*itr);
      cmdStr.append(" size 600, 400; set output \\\"data1.png\\\"; plot \\\"");
      cmdStr.append(inFileStr);
      cmdStr.append("\\\" with lines\"");
      cout << "Command: [" << cmdStr << "]" << endl;
      ::system(cmdStr.c_str());
   }

}

int main(int ac, char* av[]) {
   try
   {
      bpo::options_description cmdline_options;
      cmdline_options.add_options()
         ("version,v", "print version string")
         ("help,h", "produce help message")
         ("data,d", bpo::value<string>(), "Input data file")
         ("format,f", bpo::value<string>(), "Output file format")
         ("canvas", "Output in HTML format")
         ("dxf", "Output in DXF format (default size 120x80)")
         ("gif", "Output in GIF format")
         ("jpeg", "Output in JPEG format (uses libgd and TrueType fonts)")
         ("png", "Output in PNG images (uses libgd and TrueType fonts)")
         ("postscript", "Output in PostScript format")
         ("svg", "Output in SVG format")
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
