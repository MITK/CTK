/*=========================================================================

  Library:   CTK

  Copyright (c) PerkLab 2013

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMDisplayedFieldGeneratorDefaultRule_h
#define __ctkDICOMDisplayedFieldGeneratorDefaultRule_h

// Qt includes
#include <QStringList>

#include "ctkDICOMDisplayedFieldGeneratorAbstractRule.h"

#define EMPTY_SERIES_DESCRIPTION "Unnamed Series"

/// \ingroup DICOM_Core
///
/// Default rule for generating displayed fields from DICOM fields
class CTK_DICOM_CORE_EXPORT ctkDICOMDisplayedFieldGeneratorDefaultRule : public ctkDICOMDisplayedFieldGeneratorAbstractRule
{
public:
  /// Get name of rule
  QString name()const override;

  /// Clone displayed field generator rule. Override to return a new instance of the rule sub-class
  ctkDICOMDisplayedFieldGeneratorAbstractRule* clone() override;

  /// Specify list of DICOM tags required by the rule. These tags will be included in the tag cache
  QStringList getRequiredDICOMTags() override;

  /// Register placeholder strings that still mean that a given field can be considered empty.
  /// Used when merging the original database content with the displayed fields generated by the rules.
  /// Example: SeriesDescription -> Unnamed Series
  void registerEmptyFieldNames(QMultiMap<QString, QString> emptyFieldsSeries, QMultiMap<QString, QString> emptyFieldstudies, QMultiMap<QString, QString> emptyFieldsPatients) override;

  /// Generate displayed fields for a certain instance based on its cached tags
  /// The way these generated fields will be used is defined by \sa mergeDisplayedFieldsForInstance
  void getDisplayedFieldsForInstance(
    const QMap<QString, QString> &cachedTagsForInstance, QMap<QString, QString> &displayedFieldsForCurrentSeries,
    QMap<QString, QString> &displayedFieldsForCurrentStudy, QMap<QString, QString> &displayedFieldsForCurrentPatient ) override;

  /// Define rules of merging initial database values with new values generated by the rule plugins
  void mergeDisplayedFieldsForInstance(
    const QMap<QString, QString> &initialFieldsSeries, const QMap<QString, QString> &initialFieldsStudy, const QMap<QString, QString> &initialFieldsPatient,
    const QMap<QString, QString> &newFieldsSeries, const QMap<QString, QString> &newFieldsStudy, const QMap<QString, QString> &newFieldsPatient,
    QMap<QString, QString> &mergedFieldsSeries, QMap<QString, QString> &mergedFieldsStudy, QMap<QString, QString> &mergedFieldsPatient,
    const QMultiMap<QString, QString> &emptyFieldsSeries, const QMultiMap<QString, QString> &emptyFieldsStudy, const QMultiMap<QString, QString> &emptyFieldsPatient ) override;

protected:
  QString humanReadablePatientName(QString dicomPatientName);
};

#endif
