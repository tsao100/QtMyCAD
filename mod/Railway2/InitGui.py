# ***************************************************************************
# *   Copyright (c) 2009 Yorik van Havre <yorik@uncreated.net>              *
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU Lesser General Public License (LGPL)    *
# *   as published by the Free Software Foundation; either version 2 of     *
# *   the License, or (at your option) any later version.                   *
# *   for detail see the LICENCE text file.                                 *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU Library General Public License for more details.                  *
# *                                                                         *
# *   You should have received a copy of the GNU Library General Public     *
# *   License along with this program; if not, write to the Free Software   *
# *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
# *   USA                                                                   *
# *                                                                         *
# ***************************************************************************
"""Initialization of the Railway workbench (graphical interface)."""

import os

import FreeCAD
import FreeCADGui

__title__ = "FreeCAD Railway Workbench - Init file"
__author__ = "Yorik van Havre <yorik@uncreated.net>"
__url__ = "https://www.freecadweb.org"


class RailwayWorkbench(FreeCADGui.Workbench):
    """The Railway Workbench definition."""

    def __init__(self):
        def QT_TRANSLATE_NOOP(context, text):
            return text

        __dirname__ = os.path.join(FreeCAD.getResourceDir(), "Mod", "Railway")
        _tooltip = "The Railway workbench is used for 2D Railwaying on a grid"
        self.__class__.Icon = os.path.join(__dirname__,
                                           "Resources", "icons",
                                           "RailwayWorkbench.svg")
        self.__class__.MenuText = QT_TRANSLATE_NOOP("Railway", "Railway")
        self.__class__.ToolTip = QT_TRANSLATE_NOOP("Railway", _tooltip)

    def Initialize(self):
        """When the workbench is first loaded."""

        def QT_TRANSLATE_NOOP(context, text):
            return text

        # Run self-tests
        dependencies_OK = False
        try:
            from pivy import coin
            if FreeCADGui.getSoDBVersion() != coin.SoDB.getVersion():
                raise AssertionError("FreeCAD and Pivy use different versions "
                                     "of Coin. "
                                     "This will lead to unexpected behaviour.")
        except AssertionError:
            FreeCAD.Console.PrintWarning("Error: FreeCAD and Pivy "
                                         "use different versions of Coin. "
                                         "This will lead to unexpected "
                                         "behaviour.\n")
        except ImportError:
            FreeCAD.Console.PrintWarning("Error: Pivy not found, "
                                         "Railway Workbench will be disabled.\n")
        except Exception:
            FreeCAD.Console.PrintWarning("Error: Unknown error "
                                         "while trying to load Pivy.\n")
        else:
            dependencies_OK = True

        if not dependencies_OK:
            return

        # Import Railway tools, icons
        try:
            import Railway_rc
            import RailwayTools
            import RailwayGui
            FreeCADGui.addLanguagePath(":/translations")
            FreeCADGui.addIconPath(":/icons")
        except Exception as exc:
            FreeCAD.Console.PrintError(exc)
            FreeCAD.Console.PrintError("Error: Initializing one or more "
                                       "of the Railway modules failed, "
                                       "Railway will not work as expected.\n")

        # Set up command lists
        import Railwayutils.init_tools as it
        self.drawing_commands = it.get_Railway_drawing_commands()
        self.annotation_commands = it.get_Railway_annotation_commands()
        self.modification_commands = it.get_Railway_modification_commands()
        self.utility_commands_menu = it.get_Railway_utility_commands_menu()
        self.utility_commands_toolbar = it.get_Railway_utility_commands_toolbar()
        self.context_commands = it.get_Railway_context_commands()

        # Set up toolbars
        it.init_toolbar(self,
                        QT_TRANSLATE_NOOP("Workbench", "Railway creation tools"),
                        self.drawing_commands)
        it.init_toolbar(self,
                        QT_TRANSLATE_NOOP("Workbench", "Railway annotation tools"),
                        self.annotation_commands)
        it.init_toolbar(self,
                        QT_TRANSLATE_NOOP("Workbench", "Railway modification tools"),
                        self.modification_commands)
        it.init_toolbar(self,
                        QT_TRANSLATE_NOOP("Workbench", "Railway utility tools"),
                        self.utility_commands_toolbar)
        it.init_toolbar(self,
                        QT_TRANSLATE_NOOP("Workbench", "Railway snap"),
                        it.get_Railway_snap_commands())

        # Set up menus
        it.init_menu(self,
                     [QT_TRANSLATE_NOOP("Workbench", "&Railwaying")],
                     self.drawing_commands)
        it.init_menu(self,
                     [QT_TRANSLATE_NOOP("Workbench", "&Annotation")],
                     self.annotation_commands)
        it.init_menu(self,
                     [QT_TRANSLATE_NOOP("Workbench", "&Modification")],
                     self.modification_commands)
        it.init_menu(self,
                     [QT_TRANSLATE_NOOP("Workbench", "&Utilities")],
                     self.utility_commands_menu)

        # Set up preferences pages
        if hasattr(FreeCADGui, "RailwayToolBar"):
            if not hasattr(FreeCADGui.RailwayToolBar, "loadedPreferences"):
                FreeCADGui.addPreferencePage(":/ui/preferences-Railway.ui", QT_TRANSLATE_NOOP("Railway", "Railway"))
                FreeCADGui.addPreferencePage(":/ui/preferences-Railwayinterface.ui", QT_TRANSLATE_NOOP("Railway", "Railway"))
                FreeCADGui.addPreferencePage(":/ui/preferences-Railwaysnap.ui", QT_TRANSLATE_NOOP("Railway", "Railway"))
                FreeCADGui.addPreferencePage(":/ui/preferences-Railwayvisual.ui", QT_TRANSLATE_NOOP("Railway", "Railway"))
                FreeCADGui.addPreferencePage(":/ui/preferences-Railwaytexts.ui", QT_TRANSLATE_NOOP("Railway", "Railway"))
                FreeCADGui.RailwayToolBar.loadedPreferences = True

        FreeCADGui.getMainWindow().mainWindowClosed.connect(self.Deactivated)

        FreeCAD.Console.PrintLog('Loading Railway workbench, done.\n')

    def Activated(self):
        """When entering the workbench."""
        if hasattr(FreeCADGui, "RailwayToolBar"):
            FreeCADGui.RailwayToolBar.Activated()
        if hasattr(FreeCADGui, "Snapper"):
            FreeCADGui.Snapper.show()
            import Railwayutils.init_Railway_statusbar as dsb
            dsb.show_Railway_statusbar()
        FreeCAD.Console.PrintLog("Railway workbench activated.\n")

    def Deactivated(self):
        """When quitting the workbench."""
        if hasattr(FreeCADGui, "RailwayToolBar"):
            FreeCADGui.RailwayToolBar.Deactivated()
        if hasattr(FreeCADGui, "Snapper"):
            FreeCADGui.Snapper.hide()
            import Railwayutils.init_Railway_statusbar as dsb
            dsb.hide_Railway_statusbar()
        FreeCAD.Console.PrintLog("Railway workbench deactivated.\n")

    def ContextMenu(self, recipient):
        """Define an optional custom context menu."""
        self.appendContextMenu("Utilities", self.context_commands)

    def GetClassName(self):
        """Type of workbench."""
        return "Gui::PythonWorkbench"


FreeCADGui.addWorkbench(RailwayWorkbench)

# Preference pages for importing and exporting various file formats
# are independent of the loading of the workbench and can be loaded at startup
import Railway_rc
from PySide.QtCore import QT_TRANSLATE_NOOP
FreeCADGui.addPreferencePage(":/ui/preferences-dxf.ui", QT_TRANSLATE_NOOP("Railway", "Import-Export"))
FreeCADGui.addPreferencePage(":/ui/preferences-dwg.ui", QT_TRANSLATE_NOOP("Railway", "Import-Export"))
FreeCADGui.addPreferencePage(":/ui/preferences-svg.ui", QT_TRANSLATE_NOOP("Railway", "Import-Export"))
FreeCADGui.addPreferencePage(":/ui/preferences-oca.ui", QT_TRANSLATE_NOOP("Railway", "Import-Export"))

FreeCAD.__unit_test__ += ["TestRailwayGui"]
