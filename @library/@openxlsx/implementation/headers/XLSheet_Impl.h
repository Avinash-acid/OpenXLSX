/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXLSX_IMPL_XLABSTRACTSHEET_H
#define OPENXLSX_IMPL_XLABSTRACTSHEET_H

#include "XLAbstractXMLFile_Impl.h"
#include "XLSpreadsheetElement_Impl.h"

namespace OpenXLSX::Impl
{
    class XLContentItem;
    class XLRelationshipItem;
    class XLWorkbook;


//======================================================================================================================
//========== XLSheetType Enum ==========================================================================================
//======================================================================================================================

    /**
     * @brief The XLSheetType class is an enumeration of the available sheet types, e.g. Worksheet (ordinary
     * spreadsheets), and Chartsheet (sheets with only a chart).
     */
    enum class XLSheetType
    {
        WorkSheet, ChartSheet, DialogSheet, MacroSheet
    };


//======================================================================================================================
//========== XLSheetState Enum =========================================================================================
//======================================================================================================================

    /**
     * @brief The XLSheetState is an enumeration of the possible (visibility) states, e.g. Visible or Hidden.
     */
    enum class XLSheetState
    {
        Visible, Hidden, VeryHidden
    };


//======================================================================================================================
//========== XLSheet Class =====================================================================================
//======================================================================================================================

    /**
     * @brief The XLAbstractSheet is a generalized sheet class, which functions as superclass for specialized classes,
     * such as XLWorksheet. It implements functionality common to all sheet types. This is a pure abstract class,
     * so it cannot be instantiated.
     */
    class XLSheet: public XLAbstractXMLFile,
                   public XLSpreadsheetElement
    {
        friend class XLWorkbook;
        //friend class XLCell;


//----------------------------------------------------------------------------------------------------------------------
//           Public Member Functions
//----------------------------------------------------------------------------------------------------------------------

    public:

        /**
         * @brief The constructor. There are no default constructor, so all parameters must be provided for
         * constructing an XLAbstractSheet object. Since this is a pure abstract class, instantiation is only
         * possible via one of the derived classes.
         * @param parent A pointer to the parent XLDocument object.
         * @param name The name of the new sheet.
         * @param filepath A std::string with the relative path to the sheet file in the .xlsx package.
         * @param xmlData
         */
        XLSheet(XLWorkbook &parent,
                const std::string &name,
                const std::string &filepath,
                const std::string &xmlData = "");

        /**
         * @brief The copy constructor.
         * @param other The object to be copied.
         * @note The default copy constructor is used, i.e. only shallow copying of pointer data members.
         * @todo Can this method be deleted?
         */
        XLSheet(const XLSheet &other) = delete;

        /**
         * @brief The destructor
         * @note The default destructor is used, since cleanup of pointer data members is not required.
         */
        ~XLSheet() override;

        /**
         * @brief Assignment operator
         * @return A reference to the new object.
         * @note The default assignment operator is used, i.e. only shallow copying of pointer data members.
         * @todo Can this method be deleted?
         */
        XLSheet &operator=(const XLSheet &) = delete;

        /**
         * @brief Method to retrieve the name of the sheet.
         * @return A std::string with the sheet name.
         */
        virtual const std::string &Name() const;

        /**
         * @brief Method for renaming the sheet.
         * @param name A std::string with the new name.
         */
        virtual void SetName(const std::string &name);

        /**
         * @brief Method for getting the current visibility state of the sheet.
         * @return An XLSheetState enum object, with the current sheet state.
         */
        virtual const XLSheetState &State() const;

        /**
         * @brief Method for setting the state of the sheet.
         * @param state An XLSheetState enum object with the new state.
         */
        virtual void SetState(XLSheetState state);

        /**
         * @brief Method to get the type of the sheet.
         * @return An XLSheetType enum object with the sheet type.
         */
        virtual const XLSheetType &Type() const;

        /**
         * @brief Method for cloning the sheet.
         * @param newName A std::string with the name of the clone
         * @return A pointer to the cloned object.
         * @note This is a pure abstract method. I.e. it is implemented in subclasses.
         */
        virtual XLSheet *Clone(const std::string &newName) = 0;

        /**
         * @brief Method for getting the index of the sheet.
         * @return An int with the index of the sheet.
         */
        virtual unsigned int Index() const;

        /**
         * @brief Method for setting the index of the sheet. This effectively moves the sheet to a different position.
         */
        virtual void SetIndex();


//----------------------------------------------------------------------------------------------------------------------
//           Protected Member Functions
//----------------------------------------------------------------------------------------------------------------------

    protected:
        /**
         * @brief Method for deleting the sheet from the workbook.
         * @todo Is this the best way to do this? May end up with an invalid object.
         */
        virtual void Delete();


//----------------------------------------------------------------------------------------------------------------------
//           Private Member Variables
//----------------------------------------------------------------------------------------------------------------------

    private:
        std::string m_sheetName; /**< The sheet name given by the user */
        XLSheetType m_sheetType; /**< The sheet type, i.e. WorkSheet, ChartSheet, etc. */
        XLSheetState m_sheetState; /**< The state of the sheet, i.e. Visible, Hidden or VeryHidden */

        std::unique_ptr<XMLNode> m_nodeInWorkbook; /**< A pointer to the relevant sheet node in workbook.xml */
        std::unique_ptr<XMLNode> m_nodeInApp; /**< A pointer to the relevant TitleOfParts node in app.xml */
        XLContentItem *m_nodeInContentTypes; /**< A pointer to the relevant content type item in [Content_Types].xml */
        XLRelationshipItem *m_nodeInWorkbookRels; /**< A pointer to the relationship item in workbook.xml.rels */
    };
}

#endif //OPENXLSX_IMPL_XLABSTRACTSHEET_H