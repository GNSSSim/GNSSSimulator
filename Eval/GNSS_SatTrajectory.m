

clearvars;


filename = 'C:\Local WorkSpace\Cpp\GnssSimulator\Simulator\TrajectoryTestFiles\output_satTrajectory.txt';
fileID = fopen(filename,'r');

currentID = 0;
previousID = 0;
first_line = 1;

line_iterator = 1;  %TrajectoryMatrix lines
data_iterator = 1;  %Data lines, for TrajectoryMatrix Cell
first_data_read = 0;

%% Parse GNSS Sim Output file



while ~feof(fileID)                     
    tline = fgets(fileID);
    
    [satid x y z] = strread(tline,'%u %f %f %f');
    currentID = satid;
    if first_line
        previousID = currentID;
        first_line = 0;
    end
    
    if currentID ~= previousID  %% Data for a different satellite
        % Assemble data for current sat
        TrajectoryMatrix{line_iterator,2} = Datacell;
        % Begin new datacell for new sat
        Datacell = {0};
        data_iterator = 1;
        line_iterator = line_iterator+1;   
        first_data_read = 0;
    end
    
    if ~first_data_read
        TrajectoryMatrix{line_iterator,1} = satid;
        first_data_read = 1;
    end
    Datacell{data_iterator,1} = x;
    Datacell{data_iterator,2} = y;
    Datacell{data_iterator,3} = z;
    data_iterator = data_iterator+1;
    
    previousID = satid;  
end

% Last satellite in file
TrajectoryMatrix{line_iterator,2} = Datacell;

%% Plot data

TMsize = size(TrajectoryMatrix);
TMsize = TMsize(1);

figure;
r = 6371*1000;
[ex,ey,ez] = sphere;
surf(ex*r,ey*r,ez*r);
axis equal;
hold on;

for satit = 1:TMsize
    Datacell = TrajectoryMatrix{satit,2};
    Datasize = size(Datacell);
    Datasize = Datasize(1);
    
    graphlegend = sprintf('PRN: %d',satit);
    
    %for datait = 1:Datasize
        currx = cell2mat(Datacell(:,1));
        curry = cell2mat(Datacell(:,2));
        currz = cell2mat(Datacell(:,3));
        
        % TODO: plot vectors instead of single values....speed up things.
        plot3(currx,curry,currz,'x-','DisplayName',graphlegend);
        %plot3(currx,curry,currz,'x-')
        hold on;
        legend('-DynamicLegend','location','best');
        
   % end
end
