Mass = .5
k = 0.5
% Pick zeta, find B
%zeta = .71
%B = zeta*2*sqrt(k*Mass)  % n/(m/sec) dampning
% given B and Mass, find zeta
B = .8
zeta = B/(2*sqrt(k*Mass))

omegan = sqrt(k/Mass)  % naturalfreq
K = 1/k  % static gain

sys = tf((omegan^2)/k, [1 2*zeta*omegan omegan^2])
pole(sys)

omegad = omegan*sqrt(1-zeta^2) % damped nat freq
Td = 2*pi/omegad  % damped period
Tp = Td/2       % peak time

ymax = K*(1+exp(-zeta*omegan*Tp))       % peak magnitude 

T98 = 4/(zeta*omegan)

OmegaPeak = omegan*sqrt(1-2*zeta^2)

MagPeak = K/(2*zeta*sqrt(1-zeta^2))
dBpeak = 20*log10(MagPeak)

PhaseB1 = omegan*(1/5)^zeta
PhseB2 = omegan*5^zeta

figure(1)
PoleLoc = pole(sys);
if isreal(PoleLoc)
    xx = zeros(length(PoleLoc));
    plot( PoleLoc, xx,'*')
else
    plot(PoleLoc,'*')
end
grid on
%axis([-2.5 0 -1 1])
axis equal
hold on
title('Pole Location')
xlabel('Real Axis')
ylabel('Imaginary axis')


figure(2)
step(sys)
grid on
hold on

figure(3)
bode(sys)
grid on
hold on