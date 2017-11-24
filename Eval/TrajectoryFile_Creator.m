%% Trajectory File Creator - 
% Inputs:
%           Coordinate System - ECEF/LLH
%           Start Time
%           End time
%           Epoch interval
%           Delta-Coordinate

%% Config
clearvars;
output_path = 'C:\Local WorkSpace\Cpp\GnssSimulator\Simulator\TrajectoryTestFiles\';
output_name = 'TrajectoryFileExample_Generated_Fullday.txt';

% Coordinate System: 1 = LLH ; 0 = ECEF
coorSys = 1;

% Start time
%   GPS WEEK
start_gpswk = 1966;
%   GPS SOW
start_gpssow = 30000;         %600
% End Time
%   GPS WEEK
end_gpswk = 1966;
%   GPS SOW
end_gpssow = 60000;         % 86310

% Epoch interval [s]
epoch_delta = 10;

% Delta-Coordinate , 
if coorSys == 1
    latitude = -37.868768;
    delta_lat = 0;
    longitude = 145.124401;
    delta_long = 0;
    height = 0;
    delta_height = 0;
elseif coorSys == 0
    x = 0;
    y = 0;
    z = 0;
end

%% Main

FID = fopen([output_path output_name],'w');
% Write Header
if coorSys == 1
    header_pos = 'Position LLH';
else
    header_pos = 'Position ECEF';
end
header = sprintf('GNSS Trajectory File\n%s\nEND OF HEADER\n',header_pos);
fprintf(FID,'%s',header);

% Write Data
lines = (end_gpssow - start_gpssow)/epoch_delta; % For 1 GPSWeek currently
sow = start_gpssow;
for i = 1:lines
    gpswk = start_gpswk;
    epoch_data = sprintf('%u  %5u    ',gpswk,sow);
    coor_data = sprintf('%10.7f   %10.7f   %10.7f',latitude,longitude,height);
    
    sow = sow+epoch_delta;
    latitude = latitude + delta_lat;
    longitude = longitude + delta_long;
    height = height + delta_height;
    
    if latitude > 90
        latitude = -90;
    end
    if longitude > 180
        longitude = -180;
    end
    
    fprintf(FID,[epoch_data coor_data '\n']);
end

fclose(FID);