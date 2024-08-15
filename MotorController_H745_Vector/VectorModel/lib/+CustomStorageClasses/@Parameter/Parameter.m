classdef Parameter < Simulink.Parameter
%SimulinkDemos.Parameter  Class definition.

%   Copyright 2009-2017 The MathWorks, Inc.

  %---------------------------------------------------------------------------
  % NOTE:
  % -----
  % By default this class will use the custom storage classes from its
  % superclass.  To define your own custom storage classes:
  % - Uncomment the following method and specify the correct package name.
  % - Launch the cscdesigner for this package.
  %     >> cscdesigner('packageName');
  %
  methods
    function setupCoderInfo(h)
      % Use custom storage classes from this package
      useLocalCustomStorageClasses(h, 'CustomStorageClasses');
    end
  end % methods
  
  methods
    %---------------------------------------------------------------------------
    function h = Parameter(varargin)
      %PARAMETER  Class constructor.
      
      % Call superclass constructor with variable arguments
      h@Simulink.Parameter(varargin{:});
    end
  end
  
  methods (Access=protected)
  end
  
end % classdef
