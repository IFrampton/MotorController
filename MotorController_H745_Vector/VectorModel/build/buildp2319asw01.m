% This script is intended to be run with the file path in MATLAB set to:
% p2319asw01\asw

%clean up last build
try
    % catch error resulting if folder doesn't exist and suppress warning
    % for deleting a file on the path.
    warning('off','MATLAB:RMDIR:RemovedFromPath');
    rmdir(['build' filesep 'src'], 's');
    warning('on','MATLAB:RMDIR:RemovedFromPath');
catch
end

% build
slbuild('P2319ASW01');

% repackage
mkdir(['build' filesep 'src']);
unzip('P2319ASW01.zip','buildtemp');

cfiles = dir(['buildtemp' filesep '**' filesep '*.c']);
for i = 1:length(cfiles)
    copyfile([cfiles(i).folder filesep cfiles(i).name],['build' filesep 'src']);
end

hfiles = dir(['buildtemp' filesep '**' filesep '*.h']);
for i = 1:length(hfiles)
    copyfile([hfiles(i).folder filesep hfiles(i).name],['build' filesep 'src']);
end

% cleanup
rmdir('buildtemp', 's');
delete('p2319ASW01.zip');
Simulink.data.dictionary.closeAll('-discard')
