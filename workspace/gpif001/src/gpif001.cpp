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
#include <boost/program_options.hpp>
#include "ZiegVersion.h"

namespace po = boost::program_options;
namespace zv = ZiegVersion;
using namespace std;

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

void ParseCmdLineOpts(const po::options_description& cmdline_options,
      const po::variables_map& vm)
{
   if (vm.count("help")) {
      cout << cmdline_options << endl;
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
   if (vm.count("help,h"))
   {
   }
   if (vm.count("data,d"))
   {
   }
   bool fmtChosen(false);
   string outFmtStr("png");
   if (vm.count("format,f"))
   {
   }

   if (vm.count("canvas"))
   {
   }
   if (vm.count("dxf"))
   {
   }
   if (vm.count("gif"))
   {
   }
   if (vm.count("jpeg"))
   {
   }
   if (vm.count("png"))
   {
   }
   if (vm.count("postscript"))
   {
   }
   if (vm.count("svg"))
   {
   }

}

int main(int ac, char* av[]) {
   po::options_description cmdline_options;
   cmdline_options.add_options()
      ("version,v", "print version string")
      ("help,h", "produce help message")
      ("data,d", po::value<string>(), "Input data file")
      ("format,f", po::value<string>(), "Output file format")
      ("canvas", "Output in HTML format")
      ("dxf", "Output in DXF format (default size 120x80)")
      ("gif", "Output in GIF format")
      ("jpeg", "Output in JPEG format (uses libgd and TrueType fonts)")
      ("png", "Output in PNG images (uses libgd and TrueType fonts)")
      ("postscript", "Output in PostScript format")
      ("svg", "Output in SVG format")
   ;
   po::variables_map vm;
   po::store(po::parse_command_line(ac, av, cmdline_options), vm);
   po::notify(vm);
   ParseCmdLineOpts(cmdline_options, vm);

   cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
