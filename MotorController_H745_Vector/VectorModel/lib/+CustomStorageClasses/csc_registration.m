function defs = csc_registration(action)

%   Copyright 1994-2023 The MathWorks, Inc.
%   $Revision: $  $Date: $


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NOTE:
% - This file was automatically generated by the Simulink custom storage class
%   designer.
% - The contents of this file are arranged so that the Simulink custom storage
%   class designer can load the associated classes for editing.
% - Hand modification of this file is not recommended as it may prevent the
%   Simulink custom storage class designer from loading the associated classes.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% - Generated on:   19-Jul-2023 21:32:09
% - MATLAB version: 9.13.0.2105380 (R2022b) Update 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


switch action

  case 'CSCDefn'
    defs = [];

    h = Simulink.CSCDefn;
    set(h, 'Name', 'Calibration');
    set(h, 'OwnerPackage', 'CustomStorageClasses');
    set(h, 'CSCType', 'Unstructured');
    set(h, 'MemorySection', 'MemCalibration');
    set(h, 'IsMemorySectionInstanceSpecific', false);
    set(h, 'IsGrouped', false);
        set(h.DataUsage, 'IsParameter', true);
        set(h.DataUsage, 'IsSignal', false);
    set(h, 'DataScope', 'Exported');
    set(h, 'IsDataScopeInstanceSpecific', false);
    set(h, 'IsAutosarPerInstanceMemory', false);
    set(h, 'IsAutosarPostBuild', false);
    set(h, 'SupportSILPIL', false);
    set(h, 'DataInit', 'Auto');
    set(h, 'IsDataInitInstanceSpecific', false);
    set(h, 'DataAccess', 'Direct');
    set(h, 'IsDataAccessInstanceSpecific', false);
    set(h, 'HeaderFile', '');
    set(h, 'IsHeaderFileInstanceSpecific', true);
    set(h, 'DefinitionFile', '');
    set(h, 'IsDefinitionFileInstanceSpecific', true);
    set(h, 'Owner', '');
    set(h, 'IsOwnerInstanceSpecific', true);
    set(h, 'PreserveDimensions', false);
    set(h, 'PreserveDimensionsInstanceSpecific', true);
    set(h, 'IsReusable', false);
    set(h, 'IsReusableInstanceSpecific', false);
    set(h, 'CommentSource', 'Default');
    set(h, 'TypeComment', '');
    set(h, 'DeclareComment', '');
    set(h, 'DefineComment', '');
    set(h, 'CSCTypeAttributesClassName', '');
    set(h, 'CSCTypeAttributes', []);
    set(h, 'TLCFileName', 'Unstructured.tlc');
    defs = [defs; h];

  case 'MemorySectionDefn'
    defs = [];

    h = Simulink.MemorySectionDefn;
    set(h, 'Name', 'MemCalibration');
    set(h, 'OwnerPackage', 'CustomStorageClasses');
    set(h, 'Comment', '/* Calibration memory section */');
    set(h, 'PragmaPerVar', false);
    set(h, 'PrePragma', '');
    set(h, 'PostPragma', '');
        set(h.DataUsage, 'IsParameter', true);
        set(h.DataUsage, 'IsSignal', true);
    set(h, 'IsConst', false);
    set(h, 'IsVolatile', false);
    set(h, 'Qualifier', '__attribute__ ((section (".cal_data")))');
    defs = [defs; h];

  otherwise
    DAStudio.error('Simulink:dialog:CSCRegInvalidAction', action);
end  % switch action


%EOF
