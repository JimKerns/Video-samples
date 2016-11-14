% expected limits from step response
MaxY = 2.5
MinY = -2.5
EndTim = 80

% wheel circles
Wrad = 0:.02:2*pi;
Wx = 0.25*cos(Wrad);
Wy = 0.25*sin(Wrad);
DeltaT = 1/30;
Tim = 0:DeltaT:EndTim; %60; % time vector


%Mass = 2;
%K = .5;  % spring constant
%B = .25;  % damping

zeta = B/(2*sqrt(Mass*K))
omegam = sqrt(K/Mass)
Gain=1/K

% input
% divide time window into 3 parts. 
t13 = find(Tim<(EndTim/3),1,'last');
t23 = find(Tim>(EndTim*2/3),1); 
% three different frequencies. 
F = zeros(size(Tim));
F(1:t13)=sin(0.1*Tim(1:t13));
F(t13:t23)=sin(0.6*Tim(t13:t23));
F(t23:end)=sin(1.5*Tim(t23:end));
% step
%F = ones(length(Tim));
%F = 2*sin(Tim);  % external force


%F = 2*chirp(Tim,.01,60,.3);

% initial values
X = zeros(length(Tim)); Xdot = zeros(length(Tim)); % cart center of grav
Fk = ones(length(Tim)).*K*X(1);
Fb = ones(length(Tim)).*B*Xdot(1);
Acg = ones(length(Tim)).*(F(1)- Fb(1) - Fk(1))./Mass; % acceleration


Ycg = 2;
% plot limits
Xmin = -10;
Xmax = 10;
Ymin = 0;
Ymax = 5;

 close all
 % draw the Bode
 scrsz = get(groot,'ScreenSize');
 HH = figure('Position',[50 50 scrsz(3)*.75 scrsz(4)*.75]);
sys = tf(1,[Mass, B, K])
 bode(sys)
grid on
title('Bode Plot for Spring Mass Damper, LTU.edu')

 writerObj = VideoWriter('xx1.avi')  % create movie file
 open(writerObj)
 
%  for ii = 1:60  % two seconds of video of Bode plot
%      
%      Mv = getframe(HH);
%     writeVideo(writerObj,Mv);  % capture as video
%  end

for ii = 2:length(Tim)
    
    % differential equations.....
    Fk(ii) = K*X(ii-1);
    Fb(ii) = B*Xdot(ii-1);

    Acg(ii) = (F(ii)- Fb(ii) - Fk(ii))./Mass; % acceleration
    Xdot(ii) = Xdot(ii-1) + Acg(ii)*DeltaT; % velocity
    X(ii) = X(ii-1) + Xdot(ii)*DeltaT;
    
    close all
    % draw the picture
    HH = figure('Position',[50 50 scrsz(3)*.75 scrsz(4)*.75]);
    subplot(2,1,1)
    plot(Tim(1:ii),F(1:ii),'k', Tim(1:ii),Acg(1:ii),'g',Tim(1:ii),Xdot(1:ii),'r',Tim(1:ii),X(1:ii),'b')
    grid on
    axis([0 max(Tim) MinY MaxY])
    legend('External Force','Acceleration','Velocity','Position')
    title('Spring Mass Damper Animation, LTU.edu')
    
    
     subplot(2,1,2)
    Xcg = X(ii);

    % Plot one frame...
    patch(Xcg+[-2 2 2 -2] ,Ycg+[1.5 1.5 -1.5 -1.5],'g') % cart
    hold on
    patch(Wx+Xcg-1.8, Wy+.25,'r'); % wheel
    patch(Wx+Xcg+1.8, Wy+.25,'r'); % wheel
    plot([-10 -10 20],[5 0 0],'k','LineWidth',4) % ground and wall.
  
    plot([-10, -9, -9:((+9 +Xcg-4)/9):Xcg-4, Xcg-4, Xcg-2],...
        Ycg+1+[0 0 0 .5 -.5 .5 -.5 .5 -.5 .5 -.5 0 0 0],'r','LineWidth',2) % spring
    
    plot([-10 -9],Ycg-.8+[0 0],'b',[-9 -9],Ycg-.8+[.5 -.5],'b',...
        [Xcg-15, Xcg-4,Xcg-4,Xcg-15,],Ycg-.8+[.6 .6 -.6 -.6],'b',...
        [ Xcg-4,Xcg-2],Ycg-.8+[0 0],'b','LineWidth',2)    %  damper
    % translate from axis units to normalized plot units
    %x1 = Xcg/(Xmax-Xmin);x2 = x1+1*F;
    %y1 = (Ycg+2)/(Ymax-Ymin);
    %annotation('arrow',[x1,x2],[y1 y1])
    
    axis([Xmin Xmax Ymin Ymax])
    hold off
    
    Mv = getframe(HH);
    writeVideo(writerObj,Mv);
    
end

 close all
%  % draw the Bode
%  HH = figure('Position',[50 50 scrsz(3)*.75 scrsz(4)*.75]);
% sys = tf(1,[Mass, B, K])
%  bode(sys)
% grid on
% title('Bode Plot for Spring Mass Damper, LTU.edu')
% 
%  for ii = 1:150  % five seconds of video of Bode plot
%      
%      Mv = getframe(HH);
%     writeVideo(writerObj,Mv);  % capture as video
%  end

close(writerObj);

% display all at once
% plot(Tim(1:ii),F(1:ii),'k', Tim(1:ii),Acg(1:ii),'g',Tim(1:ii),Xdot(1:ii),'r')

disp('Done')

