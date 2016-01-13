function varargout = rec_voc(varargin)

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @rec_voc_OpeningFcn, ...
                   'gui_OutputFcn',  @rec_voc_OutputFcn, ...
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


% --- Executes just before rec_voc is made visible.
function rec_voc_OpeningFcn(hObject, eventdata, handles, varargin)

handles.output = hObject;

% Update handles structure
guidata(hObject, handles);


% --- Outputs from this function are returned to the command line.
function varargout = rec_voc_OutputFcn(hObject, eventdata, handles)

varargout{1} = handles.output;


% --- Executes on button press in grid_init.
function grid_init_Callback(hObject, eventdata, handles)


init = findobj ('TAG','init');
% init est le handler de la figure init
hold on;
%permet de superposer des graphes
axes(init);
set(init,'Xgrid','on');
set(init,'Ygrid','on');


% --- Executes on button press in grid_record.
function grid_record_Callback(hObject, eventdata, handles)



rec = findobj ('TAG','rec');
% rec est le handler de la figure rec
hold on;
%permet de superposer des graphes
axes(rec);
set(rec,'Xgrid','on');
set(rec,'Ygrid','on');


% --- Executes on button press in g_init_off.
function g_init_off_Callback(hObject, eventdata, handles)



init = findobj ('TAG','init');
% init est le handler de la figure init
hold on;
axes(init);
%permet de superposer des graphes
set(init,'Xgrid','off');
set(init,'Ygrid','off');


% --- Executes on button press in g_rec_off.
function g_rec_off_Callback(hObject, eventdata, handles)


rec = findobj ('TAG','rec');
% rec est le handler de la figure rec
hold on;
%permet de superposer des graphes
axes(rec);
set(rec,'Xgrid','off');
set(rec,'Ygrid','off');


% --- Executes on button press in init_s.
function init_s_Callback(hObject, eventdata, handles)


t= 0:1:50;
init=findobj('tag','init');
hold on;
%permet de superposer des graphes
axes(init);
%permet de definir ou le graphe doit etre trace
hold on;

% --- Executes on button press in rec_s.
function rec_s_Callback(hObject, eventdata, handles)


rec=findobj('tag','rec');
hold on;
Estimation=[]
j=0
long= length(voix)
for i=1:80:long
   j=j+1
   est=filter([0-LPC(j,2:end)],1,voix(((j*80)-79):(j*80),1))
   Estimation=[Estimation;est];

end
% --- Executes on button press in ecouter_rec.
function ecouter_rec_Callback(hObject, eventdata, handles)
    
modelname ='ecouter_rec';
stoptime = str2num(get(handles.simstoptime, 'String'));
sim(modelname, [0 stoptime])

% --- Executes on button press in ecouter.
function ecouter_Callback(hObject, eventdata, handles)

modelname ='ecouter';
stoptime = str2num(get(handles.simstoptime, 'String'));
sim(modelname, [0 stoptime])


% --- Executes on button press in enr_init.
function enr_init_Callback(hObject, eventdata, handles)


modelname ='acquisition';
stoptime = str2num(get(handles.simstoptime, 'String'));
sim(modelname, [0 stoptime])

% --- Executes on button press in enr_rec.
function enr_rec_Callback(hObject, eventdata, handles)

modelname ='acquisition_rec';
stoptime = str2num(get(handles.simstoptime, 'String'));
sim(modelname, [0 stoptime])


% --- Executes on button press in stop_ecouter.
function stop_ecouter_Callback(hObject, eventdata, handles)

global GUIStopFlag;
GUIStopFlag = 1;

% --- Executes on button press in Stop_rec.
function Stop_rec_Callback(hObject, eventdata, handles)

global GUIStopFlag;
GUIStopFlag = 1;



% --- Executes during object creation, after setting all properties.
function simstoptime_CreateFcn(hObject, eventdata, handles)

if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function simstoptime_Callback(hObject, eventdata, handles)
% rien a mettre dans cette fonction


% --- Executes on button press in stop_ecouter_rec.
function stop_ecouter_rec_Callback(hObject, eventdata, handles)

global GUIStopFlag;
GUIStopFlag = 1;

% --- Executes on button press in stop_rec_rec.
function stop_rec_rec_Callback(hObject, eventdata, handles)

global GUIStopFlag;
GUIStopFlag = 1;


% --- Executes during object creation, after setting all properties.
function formant_CreateFcn(hObject, eventdata, handles)
% hObject    handle to formant (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end


% --- Executes on selection change in formant.
function formant_Callback(hObject, eventdata, handles)



% --- Executes on button press in lpc.
function lpc_Callback(hObject, eventdata, handles)

sim('LPC');

% --- Executes on button press in lpc_rec.
function lpc_rec_Callback(hObject, eventdata, handles)

sim('LPC_rec');


% --- Executes on button press in est_init.
function est_init_Callback(hObject, eventdata, handles)



% --- Executes on button press in est_rec.
function est_rec_Callback(hObject, eventdata, handles)



