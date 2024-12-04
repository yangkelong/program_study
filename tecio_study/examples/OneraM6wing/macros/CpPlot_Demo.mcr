#!MC 1120

######################### Place this in tecplot.mcr ########################
#
# $!MacroFunction NAME = "Run CP plot"
#   ShowInMacroPanel = TRUE
#   $!INCLUDEMACRO "PATH/TO/MACRO/THISFILE.mcr"
# $!EndMacroFunction
#
############################################################################

$!PROMPTFORTEXTSTRING |CPVARNUM|
  INSTRUCTIONS = "Enter variable number for Pressure Coefficient"

$!VarSet |FIRSTSLICEZONE| = 0 #Invalid
$!VarSet |INITZONES| = |NUMZONES|


# Extract Slices
$!EXTRACTSLICES 

$!VarSet |FINALZONES| = |NUMZONES| 
$!VarSet |NEWZONECOUNT| = (|FINALZONES| - |INITZONES|)

$!IF |NEWZONECOUNT| > 0 #If extraction was successful

    $!GETVARNUMBYNAME |XOverL|
      NAME = "X/L"

    $!IF |XOverL| == 0 # Doesn't exist yet
      # "X/L" needs to be defined for all zones before we can
      # calculate it for individual zones, so we create it here.
      $!ALTERDATA 
        EQUATION = '{X/L} = 0'
    $!ENDIF

    #Ensure that we have a valid X/L variable number
    $!GETVARNUMBYNAME |XOverL|
      NAME = "X/L"
    
    # Get current active zones and set it to ORIGACTIVEZONES variable. 
    $!EXTENDEDCOMMAND COMMANDPROCESSORID='extendmcr'
      COMMAND='QUERY.ACTIVEZONES ORIGACTIVEZONES'

    # Loop over all the new zones. Need to activate the zones
    # one at a time to use MINX and MAXX intrinsic variables
    # which return the min and max X value for active zones
    
    $!VARSET |FIRSTSLICEZONE| = (|INITZONES| + 1)
    $!VARSET |SLICEZONE| = |FIRSTSLICEZONE|
    $!LOOP |NEWZONECOUNT|
      $!ACTIVEFIELDMAPS = [|SLICEZONE|]
      $!ALTERDATA  [|SLICEZONE|]
        EQUATION = '{X/L} = ({X} - MINX)/(MAXX-MINX)'
      $!VarSet |SLICEZONE| += 1
    $!ENDLOOP

    # Since we've modified the active zones, we restore them here.
    $!ACTIVEFIELDMAPS = [|ORIGACTIVEZONES|]

    #Create new XY line frame and tile so they both fit in view nicely
    $!CREATENEWFRAME 
    $!EXTENDEDCOMMAND 
      COMMANDPROCESSORID = 'Multi Frame Manager'
      COMMAND = 'TILEFRAMESHORIZ'  
    $!WORKSPACEVIEW FITALLFRAMES
    $!PLOTTYPE = XYLINE
    $!DELETELINEMAPS 

    # Loop over all the new zones and create new
    # line maps for each of the new zones

    $!VarSet |CURZONE| = |FIRSTSLICEZONE|
    $!LOOP |NEWZONECOUNT|
      $!CREATELINEMAP 
      $!LINEMAP [|LOOP|]  NAME = '&ZN&'
      $!LINEMAP [|LOOP|]  ASSIGN{YAXISVAR = |CPVARNUM|}
      $!LINEMAP [|LOOP|]  ASSIGN{XAXISVAR = |XOverL|}
      $!LINEMAP [|LOOP|]  ASSIGN{ZONE = |CURZONE|}
      $!VarSet |CURZONE| += 1
    $!ENDLOOP

    # If we're extracting "start", "end" and "intermediate" slice, the
    # "end" slice ends up being the second linemap, which we push to the
    # bottom here so they're listed in order.  If we also extract the primary
    # slice, this code would need to push #3 to the bottom, so this is a
    # special case...
    $!IF |NUMLINEMAPS| >= 2
        $!SHIFTLINEMAPSTOBOTTOM [2]
    $!ENDIF

    $!ACTIVELINEMAPS = [1-|NUMLINEMAPS|]

    $!XYLINEAXIS AXISMODE = INDEPENDENT
    $!VIEW DATAFIT
    $!XYLINEAXIS YDETAIL 1 {ISREVERSED = YES}

    $!GLOBALLINEPLOT LEGEND{SHOW = YES}
    $!GLOBALLINEPLOT LEGEND{TEXTSHAPE{SIZEUNITS = POINT}}
    $!GLOBALLINEPLOT LEGEND{TEXTSHAPE{HEIGHT = 8}}
    $!GLOBALLINEPLOT LEGEND{XYPOS{Y = 95}}
    $!GLOBALLINEPLOT LEGEND{XYPOS{X = 98}}
$!ENDIF

