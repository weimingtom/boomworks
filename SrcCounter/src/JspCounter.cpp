///////////////////////////////////////////////////////////////////////
// JspCounter.cpp: implementation of the JspCounter class.
///////////////////////////////////////////////////////////////////////

#include <wx/textfile.h>
#include "JspCounter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

wxString JspCounter::ms_strType = _T("JSP");

JspCounter::JspCounter()
{
}

JspCounter::~JspCounter()
{
}

void JspCounter::countingSourceFile(wxTextFile& file, int& nLines, int& nCodeLines,
                                     int& nCommentLines, int& nCodeCommentLines, int& nBlankLines )
{
    //
    wxString bufCurLine;

    BOOL bHasSettedCodeFlag	= FALSE;	//AΛΞRΔ΄ o"<%"―TRUE, "%>"―FALSE
    // BOOL bHasSettedCommentFlag	= FALSE;	//u¬RΔ΄ ΥΜΉΞoδϋτ"―TRUE, aΉΞoδϋτ"―FALSE

    BOOL bStatisticedAsComment	= FALSE;	//]Ξ¨AΛΞΕΟRΔ
    BOOL bStatisticedAsCode		= FALSE;	//]Ξ¨ψιΞΕΟRΔ

    int nLen = 0;

    //while( file.ReadString( bufCurLine ))
    for ( bufCurLine = file.GetFirstLine(); !file.Eof(); bufCurLine = file.GetNextLine() )
    {
        // Total lines
        nLines++;

        bStatisticedAsComment	= FALSE;	//]Ξ¨AΛΞΕΟRΔ
        bStatisticedAsCode		= FALSE;	//]Ξ¨ψιΞΕΟRΔ

        bufCurLine.Trim(false);

        if ( 0 == bufCurLine.Len() )
        {// Counting blank lines
            nBlankLines++;
            continue;
        }

        //////////////////////////////////////////////////////////////////////////

        bufCurLine.Trim();

        nLen = bufCurLine.Len();

        if (nLen < 2)
        {
            if (bHasSettedCodeFlag)
            {
                nCodeLines++;
                continue;
            }
            else
            {

            }
        }

        //////////////////////////////////////////////////////////////////////////

        if ( !bHasSettedCodeFlag
                && bufCurLine[ 0 ]			==  _T( '<' )
                && bufCurLine[ 1 ]			==	_T( '%' )
                && bufCurLine[ nLen - 2 ]	==	_T( '%' )
                && bufCurLine[ nLen - 1 ]	==  _T( '>' ))
        {
            nCodeLines++;
            continue;
        }
        else if ( !bHasSettedCodeFlag
                  && bufCurLine.Find( _T( "<%" )) != -1
                  && bufCurLine.Find( _T( "%>" )) != -1 )
        {
            //nCommentLines++;
            nCodeLines++;
            continue;
        }

        //////////////////////////////////////////////////////////////////////////

        if ( !bHasSettedCodeFlag
                && bufCurLine[ 0 ]			==  _T( '<' )
                && bufCurLine[ 1 ]			==	_T( '%' )
                && bufCurLine.Find( _T( "%>" )) == -1 )
        {
            bHasSettedCodeFlag = TRUE;
            nCodeLines++;
            continue;
        }

        if (bHasSettedCodeFlag
                && bufCurLine[ nLen - 2 ]	!=	_T( '%' )
                && bufCurLine[ nLen - 1 ]	!=  _T( '>' ) )
        {//
            if ( bufCurLine[0]	== _T( '/' )
                    && bufCurLine[1]		== _T( '/' ) )
            {
                nCommentLines++;
                continue;
            }
            else if ( bufCurLine.Find( _T( "//" )) != -1 )
            { // ΫΉ[Ε ΉΞνo''cΘΰ
                nCommentLines++;
                nCodeLines++;
                continue;
            }

        }
        else if ( bHasSettedCodeFlag
                  && bufCurLine[ nLen - 2 ]	==	_T( '%' )
                  && bufCurLine[ nLen - 1 ]	==  _T( '>' ))
        {
            bHasSettedCodeFlag = FALSE;
            nCodeLines++;
            continue;
        }

		///////////////////////////////////////////////////////////////

        if ( bufCurLine.Find( _T( "//" ) ) == -1
                && bufCurLine.Find( _T( "<%" ) ) == -1
                && bufCurLine.Find( _T( "%>" ) ) == -1 )
        { //ε]Ξχ]ΛάAΛEπ¨ΉΕAΛΞE¨ΉΕψιΞ
            if ( bHasSettedCodeFlag )
            {
                nCodeLines++;
                continue;
            }
            else
            {
                //nCommentLines++;
                continue;
            }
        }

    }// End for
}
