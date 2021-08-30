/*
 * Copyright (c)2006-2010  Hanchuan Peng (Janelia Farm, Howard Hughes Medical Institute).
 * All rights reserved.
 */


/************
                                            ********* LICENSE NOTICE ************

This folder contains all source codes for the V3D project, which is subject to the following conditions if you want to use it.

You will ***have to agree*** the following terms, *before* downloading/using/running/editing/changing any portion of codes in this package.

1. This package is free for non-profit research, but needs a special license for any commercial purpose. Please contact Hanchuan Peng for details.

2. You agree to appropriately cite this work in your related studies and publications.

Peng, H., Ruan, Z., Long, F., Simpson, J.H., and Myers, E.W. (2010) “V3D enables real-time 3D visualization and quantitative analysis of large-scale biological image data sets,” Nature Biotechnology, Vol. 28, No. 4, pp. 348-353, DOI: 10.1038/nbt.1612. ( http://penglab.janelia.org/papersall/docpdf/2010_NBT_V3D.pdf )

Peng, H, Ruan, Z., Atasoy, D., and Sternson, S. (2010) “Automatic reconstruction of 3D neuron structures using a graph-augmented deformable model,” Bioinformatics, Vol. 26, pp. i38-i46, 2010. ( http://penglab.janelia.org/papersall/docpdf/2010_Bioinfo_GD_ISMB2010.pdf )

3. This software is provided by the copyright holders (Hanchuan Peng), Howard Hughes Medical Institute, Janelia Farm Research Campus, and contributors "as is" and any express or implied warranties, including, but not limited to, any implied warranties of merchantability, non-infringement, or fitness for a particular purpose are disclaimed. In no event shall the copyright owner, Howard Hughes Medical Institute, Janelia Farm Research Campus, or contributors be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; loss of use, data, or profits; reasonable royalties; or business interruption) however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of the use of this software, even if advised of the possibility of such damage.

4. Neither the name of the Howard Hughes Medical Institute, Janelia Farm Research Campus, nor Hanchuan Peng, may be used to endorse or promote products derived from this software without specific prior written permission.

*************/



//---
/****************************************************************************
**
V3D main program

By Hanchuan Peng

July 21, 2006
060924: v3d v1.2

Last update: 2008-04-25: try to add command line based utilities
Last update: 2010-04-12: add a global try-catch to catch all exceptions
Last update: 2010-11-19: change some of the help info
Last update: 2011-04-19: fix some potential problem of null mainWin pointer
Last update: 2011-08-25: remove some uncalled old code, and adjust the inconsistent return values of the main function

****************************************************************************/

#define COMPILE_TO_COMMANDLINE 1

#include "../3drenderer/v3dr_common.h"

#include "v3d_compile_constraints.h"

#include <QApplication>
#include <QFile>

#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "v3d_application.h"
#include "customdebug.h"

#include <string>
using namespace std;

#include "v3d_core.h"

#include "v3d_commandlineparser.h"
//#include "v3d_version_info.h"
//#include "../plugin_loader/v3d_plugin_loader.h"

//void printHelp_v3d();
//void printHelp_align();
//void printHelp_straight();
//void printHelp_trace();

V3dApplication* V3dApplication::theApp = 0;
//
//void printHelp_v3d()
//{
//	cout<<endl<<"Vaa3D: a 3D image visualization and analysis platform developed by Hanchuan Peng and colleagues."<<endl;
//	cout<<endl<<"Usage: v3d -h -M moduleCode [all other options specific to different modules]"<<endl;
//
//	cout<<"    -h/H         help information."<<endl;
//
//	cout<<"    -i <file>                    open single or multiple image (.tif/.tiff, .lsm, .mrc, .raw/.v3draw) / object (.ano, .apo, .swc, .marker) files"<<endl;
//    cout<<"    -o <file>                    indicates single or multiple outputs"<<endl;
//	cout<<"    -x <plugin_dll_full_path or unique partial path>    a string indicates the full path or a unique partial path of a dll (for a plugin) to be launched."<<endl;
//	cout<<"    -m <menu_name>               a string indicates which menu of a plugin will be called."<<endl;
//    cout<<"    -f <function_name>           a string indicates which function of a plugin will be called."<<endl;
//    cout<<"    -p <parameters>              a string indicates parameters that plugin function use"<<endl;
//    cout<<"    -pf <configuration>          a string read from configuration file indicates parameters that plugin function use"<<endl;
//
//	cout<<"    -v                           force to open a 3d viewer when loading an image, otherwise use the default v3d global setting (from \"Adjust Preference\")"<<endl;
//    cout<<"    -na                          open NeuronAnnotator work-mode directly"<<endl;
//    cout<<"    -cmd  [headless command-line arguments, intended for compute grid use. Try \'-cmd -h\' for more information on this option]"<<endl;
//
//    //added by Hanchuan Peng, 20120217
//    V3dApplication* app = V3dApplication::getInstance();
//    if (!app) return;
//    MainWindow* mainWin=app->getMainWindow();
//    if (!mainWin) return;
//
//    /*QStringList existingPluginsList = mainWin->pluginLoader->getPluginNameList();
//    if (existingPluginsList.size()>0)
//        cout << endl << "Found [" << existingPluginsList.size() << "] plugins"<<endl;
//    for (int i=0;i<existingPluginsList.size();i++)
//        cout << "#" << i+1 << "          " << existingPluginsList.at(i).toLocal8Bit().constData() << endl;*/
//
//	return;
//}

int main(int argc, char **argv)
{
	printf("Hello World!\n\n");
	Q_INIT_RESOURCE(v3d);
	V3dApplication* app = V3dApplication::getInstance(argc, argv);
	app->activateMainWindow();
	MainWindow* mainWin = app->getMainWindow();
	app->installEventFilter(mainWin);
	mainWin->show();
	return app->exec();

	//for (int myii=0; myii<argc;myii++)
	//{
	//	v3d_msg(QString("[%1]").arg(argv[myii]));
	//}

	//CLP parser;

	//parser.parse(argc, argv, printHelp_v3d); // parse command lines to v3d_cl_interface Nov. 23, 2010 by YuY

	//if(parser.i_v3d.clp_finished)
	//{
	//	return false;
	//}
	//else
	//{
	//	if(parser.i_v3d.openV3D)
	//	{
	//		// ------ V3D GUI handling module ---------------------
	//		Q_INIT_RESOURCE(v3d);

 //           V3dApplication* app = V3dApplication::getInstance(argc, argv);
 //           if(!parser.i_v3d.hideV3D)
 //           {
 //               app->activateMainWindow();
 //           }

 //           MainWindow* mainWin=app->getMainWindow();

	//		if (!mainWin)
	//		{
	//			v3d_msg("Unable to open the Vaa3D main window. Quit.");
	//			return false;
	//		}

 //           app->installEventFilter(mainWin);

 //           if (mainWin)
 //           {
 //               mainWin->v3dclp.copy(parser.i_v3d);

 //               if(!parser.i_v3d.hideV3D)
 //               {
 //                   mainWin->show();
 //               }
 //           }

	//		// launch v3d
	//		try
	//		{
 //               if(!parser.i_v3d.hideV3D)
 //                   return app->exec();
 //               else
 //                   return false;
	//		}
	//		catch (...)
	//		{
	//			v3d_msg("Catch an exception at the main application level. Basically you should never see this. Please click Ok to quit and send the error log to the Vaa3D developers to figure out the problem.");
	//			return false;
	//		}
	//		// -------------------------------------------------------

	//	}
	//	else
	//	{
	//		return false;
	//	}

	//}

}
