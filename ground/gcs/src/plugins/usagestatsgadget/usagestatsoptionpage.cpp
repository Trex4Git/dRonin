/**
 ******************************************************************************
 * @file       usagestatsoptionpage.cpp
 * @author     dRonin, http://dRonin.org/, Copyright (C) 2015
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UsageStatsOptionPage
 * @{
 * @brief [Brief]
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "usagestatsoptionpage.h"
#include "ui_usagestatsoptionpage.h"
#include "usagestatsplugin.h"

UsageStatsOptionPage::UsageStatsOptionPage(QObject *parent) :
    IOptionsPage(parent)
{
    m_config=qobject_cast<UsageStatsPlugin *>(parent);
    connect(this,SIGNAL(settingsUpdated()),m_config,SLOT(updateSettings()));
}
UsageStatsOptionPage::~UsageStatsOptionPage()
{
}
QWidget *UsageStatsOptionPage::createPage(QWidget *parent)
{

    m_page = new Ui::UsageStatsOptionPage();
    QWidget *w = new QWidget(parent);
    m_page->setupUi(w);
    m_page->cb_AllowSending->setChecked(m_config->getSendUsageStats());
    m_page->cb_AllowPrivate->setChecked(m_config->getSendPrivateData());
    m_page->label_UUID->setText(QString("UUID: ")+m_config->getInstallationUUID());
    return w;
}

void UsageStatsOptionPage::apply()
{
    m_config->setSendUsageStats(m_page->cb_AllowSending->isChecked());
    m_config->setSendPrivateData(m_page->cb_AllowPrivate->isChecked());
    emit settingsUpdated();
}

void UsageStatsOptionPage::finish()
{
    delete m_page;
}
