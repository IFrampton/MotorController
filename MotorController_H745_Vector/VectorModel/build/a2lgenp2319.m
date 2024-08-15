% This script is intended to be run with the file path in MATLAB set to:
% p2319asw01\asw

% Generate ASW A2L
ASWA2LFolder = './build/bin';
ASWA2LFileName = 'P2319ASW01';
CSWBinFolder = '../../../bin';
CSWELFFileName = 'P2319CSW03_latest';

load_system('P2319ASW01');
coder.asap2.export('P2319ASW01', ...
    FileName                    =ASWA2LFileName, ...
    Folder                      =ASWA2LFolder, ...
    Version                     ='1.71', ...
    Comments                    =true, ...
    SupportStructureElements    =false);

% Generate CSW A2L
BSWA2LFolder = '../../../src';
BSWA2LFileName = 'P2319BSW';
CSWA2LFileName = 'P2319CSW03';

ASWFID = fopen([ASWA2LFolder '/' ASWA2LFileName '.a2l'],'r');
BSWFID = fopen([BSWA2LFolder '/' BSWA2LFileName '.a2l'],'r');
CSWFID = fopen([ASWA2LFolder '/' CSWA2LFileName '.a2l'],'w');

PrintingState = 0; 
% 0 - BSW header, 1 - ASW header, 2 - ASW body, 3 - BSW footer, 4 - done

while PrintingState ~= 4
    if PrintingState == 0
        % BSW Header
        BSWLine = fgets(BSWFID);
        if contains(BSWLine,'/* @ASW_OBJ_DEFINITIONS@ */')
            PrintingState = 1;
        else
            BSWLine = strrep(BSWLine,'%','%%');
            fprintf(CSWFID,BSWLine);
        end
    elseif PrintingState == 1
        % ASW Header
        ASWLine = fgets(ASWFID);
        if contains(ASWLine, '/begin CHARACTERISTIC')
            ASWLine = strrep(ASWLine,'%','%%');
            fprintf(CSWFID,ASWLine);
            PrintingState = 2;
        end
    elseif PrintingState == 2
        % ASW Body
        ASWLine = fgets(ASWFID);
        if contains(ASWLine, '/end MODULE')
            PrintingState = 3;
        else
            ASWLine = strrep(ASWLine,'%','%%');
            fprintf(CSWFID,ASWLine);
        end
    elseif PrintingState == 3
        % BSW footer
        BSWLine = fgets(BSWFID);
        if BSWLine == -1
            PrintingState = 4;
        else
            BSWLine = strrep(BSWLine,'%','%%');
            fprintf(CSWFID,BSWLine);
        end
    else
        error('Reached an invalid state while generating CSW A2L file.')
    end
end

fclose(ASWFID);
fclose(BSWFID);
fclose(CSWFID);

% Populate ECU addresses from the ELF file
rtw.asap2SetAddress([ASWA2LFolder '/' CSWA2LFileName '.a2l'], ...
                    [CSWBinFolder '/' CSWELFFileName '.elf'])
