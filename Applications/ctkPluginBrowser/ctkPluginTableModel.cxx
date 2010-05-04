/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include "ctkPluginTableModel.h"

#include <ctkPlugin.h>
#include <ctkPluginContext.h>

namespace ctk {

  PluginTableModel::PluginTableModel(PluginContext* pc, QObject* parent)
    : QAbstractTableModel(parent)
  {
    plugins = pc->getPlugins();
  }

  QVariant PluginTableModel::data(const QModelIndex& index, int role) const
  {
    if (!index.isValid()) return QVariant();

    Plugin* plugin = plugins.at(index.row());
    if (role == Qt::DisplayRole)
    {
      int col = index.column();
      if (col == 0)
      {
        return QVariant(plugin->getSymbolicName());
      }
      else if (col == 1)
      {
        return QVariant(plugin->getVersion().toString());
      }
      else if (col == 2)
      {
        return QVariant(getStringForState(plugin->getState()));
      }
    }
    else if (role == Qt::UserRole)
    {
      return plugin->getPluginId();
    }

    return QVariant();
  }

  QVariant PluginTableModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
      if (section == 0)
      {
        return QVariant("Plugin");
      }
      else if (section == 1)
      {
        return QVariant("Version");
      }
      else if (section == 2)
      {
        return QVariant("State");
      }
    }

    return QVariant();
  }

  int PluginTableModel::columnCount(const QModelIndex& parent) const
  {
    return 3;
  }

  int PluginTableModel::rowCount(const QModelIndex& parent) const
  {
    return plugins.size();
  }

  QString PluginTableModel::getStringForState(const Plugin::State state) const
  {
    static const QString uninstalled("UNINSTALLED");
    static const QString installed("INSTALLED");
    static const QString resolved("RESOLVED");
    static const QString starting("STARTING");
    static const QString stopping("STOPPING");
    static const QString active("ACTIVE");

    switch(state)
    {
    case Plugin::UNINSTALLED: return uninstalled;
    case Plugin::INSTALLED: return installed;
    case Plugin::RESOLVED: return resolved;
    case Plugin::STARTING: return starting;
    case Plugin::STOPPING: return stopping;
    case Plugin::ACTIVE: return active;
    default: return QString("unknown");
    }
  }

}
