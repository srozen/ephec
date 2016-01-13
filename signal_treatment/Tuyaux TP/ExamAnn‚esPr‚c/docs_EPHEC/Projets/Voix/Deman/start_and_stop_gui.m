function varargout = start_and_stop_gui(varargin)
% START_AND_STOP_GUI M-file for start_and_stop_gui.fig
%      START_AND_STOP_GUI, by itself, creates a new START_AND_STOP_GUI or raises the existing
%      singleton*.
%
%      H = START_AND_STOP_GUI returns the handle to a new START_AND_STOP_GUI or the handle to
%      the existing singleton*.
%
%      START_AND_STOP_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in START_AND_STOP_GUI.M with the given input arguments.
%
%      START_AND_STOP_GUI('Property','Value',...) creates a new START_AND_STOP_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before start_and_stop_gui_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to start_and_stop_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help start_and_stop_gui

% Last Modified by GUIDE v2.5 03-Mar-2003 16:19:24

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @start_and_stop_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @start_and_stop_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin & isstr(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before start_and_stop_gui is made visible.
function start_and_stop_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to start_and_stop_gui (see VARARGIN)

% Choose default command line output for start_and_stop_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes start_and_stop_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = start_and_stop_gui_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in startsim.
function startsim_Callback(hObject, eventdata, handles)
% hObject    handle to startsim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
modelname = get(handles.modelname, 'String');
stoptime = str2num(get(handles.simstoptime, 'String'));
sim(modelname, [0 stoptime])


% --- Executes on button press in stopsim.
function stopsim_Callback(hObject, eventdata, handles)
% hObject    handle to stopsim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global GUIStopFlag;
GUIStopFlag = 1;


% --- Executes during object creation, after setting all properties.
function modelname_CreateFcn(hObject, eventdata, handles)
% hObject    handle to modelname (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function modelname_Callback(hObject, eventdata, handles)
% hObject    handle to modelname (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of modelname as text
%        str2double(get(hObject,'String')) returns contents of modelname as a double


% --- Executes during object creation, after setting all properties.
function simstoptime_CreateFcn(hObject, eventdata, handles)
% hObject    handle to simstoptime (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function simstoptime_Callback(hObject, eventdata, handles)
% hObject    handle to simstoptime (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of simstoptime as text
%        str2double(get(hObject,'String')) returns contents of simstoptime as a double


