import serial
import serial.tools.list_ports as list_ports
import string, array

class oscope:

    def __init__(self, port = ''):
        self.FCY = 16e6
        self.TCY = 62.5e-9
        self.timer_multipliers = [self.TCY, 8. * self.TCY, 64. * self.TCY, 256. * self.TCY]

        self.SCOPE_BUFFER_SIZE = 3000

        self.volts_per_lsb = (5e-3, 1e-3)

        self.ch1_zero = [[2048., 2048.], 
                         [2048., 2048.], 
                         [2048., 2048.], 
                         [2048., 2048.], 
                         [2048., 2048.]]
        self.ch2_zero = [[2048., 2048.], 
                         [2048., 2048.], 
                         [2048., 2048.], 
                         [2048., 2048.], 
                         [2048., 2048.]]

        self.ch1_zero_4MSps = [2048., 2048.]
        self.ch2_zero_4MSps = [2048., 2048.]

        self.ch1_gain = [[1., 1.], 
                         [1., 1.], 
                         [1., 1.], 
                         [1., 1.], 
                         [1., 1.]]
        self.ch2_gain = [[1., 1.], 
                         [1., 1.], 
                         [1., 1.], 
                         [1., 1.], 
                         [1., 1.]]

        self.ch1_gain_4MSps = [1., 1.]
        self.ch2_gain_4MSps = [1., 1.]

        self.MCLK_FREQ = 4e6

        self.shapes = ('DC', 'SIN', 'SQUARE', 'TRIANGLE')

        self.wg_sq_gain = [1., 1.]
        self.wg_nsq_gain = [1., 1.]

        self.vo_gain = 1.
        self.vo_zero = 0.

        if port == '':
            self.dev = None
            self.connected = False
            devices = list_ports.comports()
            for device in devices:
                if device.vid == 0x6666 and device.pid == 0xCDC:
                    try:
                        self.dev = serial.Serial(device.device)
                        self.connected = True
                        print('Connected to {!s}...'.format(device.device))
                    except:
                        pass
                if self.connected:
                    break
        else:
            try:
                self.dev = serial.Serial(port)
                self.connected = True
            except:
                self.dev = None
                self.connected = False

        if self.connected:
            self.write('')
            self.num_avg = self.get_num_avg()
            self.sampling_interval = self.get_period()
            self.ch1_range = self.get_ch1range()
            self.ch2_range = self.get_ch2range()
            self.read_calibration_vals()

    def write(self, command):
        if self.connected:
            self.dev.write('{!s}\r'.format(command).encode())

    def read(self):
        if self.connected:
            return self.dev.readline().decode()

    def toggle_led1(self):
        if self.connected:
            self.write('UI:LED1 TOGGLE')

    def set_led1(self, val):
        if self.connected:
            self.write('UI:LED1 {:X}'.format(int(val)))

    def get_led1(self):
        if self.connected:
            self.write('UI:LED1?')
            return int(self.read())

    def toggle_led2(self):
        if self.connected:
            self.write('UI:LED2 TOGGLE')

    def set_led2(self, val):
        if self.connected:
            self.write('UI:LED2 {:X}'.format(int(val)))

    def get_led2(self):
        if self.connected:
            self.write('UI:LED2?')
            return int(self.read())

    def toggle_led3(self):
        if self.connected:
            self.write('UI:LED3 TOGGLE')

    def set_led3(self, val):
        if self.connected:
            self.write('UI:LED3 {:X}'.format(int(val)))

    def get_led3(self):
        if self.connected:
            self.write('UI:LED3?')
            return int(self.read())

    def read_sw1(self):
        if self.connected:
            self.write('UI:SW1?')
            return int(self.read())

    def set_ch1gain(self, val):
        if self.connected:
            self.write('SCOPE:CH1GAIN {:X}'.format(int(val)))

    def get_ch1gain(self):
        if self.connected:
            self.write('SCOPE:CH1GAIN?')
            return int(self.read(), 16)

    def set_ch2gain(self, val):
        if self.connected:
            self.write('SCOPE:CH2GAIN {:X}'.format(int(val)))

    def get_ch2gain(self):
        if self.connected:
            self.write('SCOPE:CH2GAIN?')
            return int(self.read(), 16)

    def dig_set_mode(self, pin, mode):
        if self.connected:
            self.write('DIG:MODE {:X},{:X}'.format(int(pin), int(mode)))

    def dig_get_mode(self, pin):
        if self.connected:
            self.write('DIG:MODE? {:X}'.format(int(pin)))
            return int(self.read(), 16)

    def dig_set(self, pin):
        if self.connected:
            self.write('DIG:SET {:X}'.format(int(pin)))

    def dig_clear(self, pin):
        if self.connected:
            self.write('DIG:CLEAR {:X}'.format(int(pin)))

    def dig_toggle(self, pin):
        if self.connected:
            self.write('DIG:TOGGLE {:X}'.format(int(pin)))

    def dig_write(self, pin, val):
        if self.connected:
            self.write('DIG:WRITE {:X},{:X}'.format(int(pin), int(val)))

    def dig_read(self, pin):
        if self.connected:
            self.write('DIG:READ {:X}'.format(int(pin)))
            return int(self.read(), 16)

    def dig_set_od(self, pin, val):
        if self.connected:
            self.write('DIG:OD {:X},{:X}'.format(int(pin), int(val)))

    def dig_get_od(self, pin):
        if self.connected:
            self.write('DIG:OD? {:X}'.format(int(pin)))
            return int(self.read(), 16)

    def dig_set_freq(self, pin, freq):
        if self.connected:
            val = int(self.FCY / freq - 1.)
            val = val if val < 65536 else 65535
            self.write('DIG:PERIOD {:X},{:X}'.format(int(pin), val))

    def dig_get_freq(self, pin):
        if self.connected:
            self.write('DIG:PERIOD? {:X}'.format(int(pin)))
            val = int(self.read(), 16)
            return self.FCY / (val + 1.)

    def dig_set_duty(self, pin, duty):
        if self.connected:
            val = int(65536 * duty)
            val = val if val < 65536 else 65535
            self.write('DIG:DUTY {:X},{:X}'.format(int(pin), val))

    def dig_get_duty(self, pin):
        if self.connected:
            self.write('DIG:DUTY? {:X}'.format(int(pin)))
            val = int(self.read(), 16)
            return val / 65536.

    def dig_set_width(self, pin, width):
        if self.connected:
            val = int(self.FCY * width + 0.5)
            val = val if val > 1 else 1
            val = val if val < 65535 else 65535
            self.write('DIG:WIDTH {:X},{:X}'.format(int(pin), val))

    def dig_get_width(self, pin):
        if self.connected:
            self.write('DIG:WIDTH? {:X}'.format(int(pin)))
            val = int(self.read(), 16)
            return val * self.TCY

    def dig_set_period(self, period):
        if self.connected:
            if period > 256. * 65536. * self.TCY:
                return
            elif period > 64. * 65536. * self.TCY:
                T1CON = 0x0030
                PR1 = int(period * (self.FCY / 256.)) - 1
            elif period > 8. * 65536. * self.TCY:
                T1CON = 0x0020
                PR1 = int(period * (self.FCY / 64.)) - 1
            elif period > 65536. * self.TCY:
                T1CON = 0x0010
                PR1 = int(period * (self.FCY / 8.)) - 1
            elif period >= 8. * self.TCY:
                T1CON = 0x0000
                PR1 = int(period * self.FCY) - 1
            else:
                return
            self.write('DIG:T1PERIOD {:X},{:X}'.format(PR1, T1CON))

    def dig_get_period(self):
        if self.connected:
            self.write('DIG:T1PERIOD?')
            vals = self.read().split(',')
            PR1 = int(vals[0], 16)
            T1CON = int(vals[1], 16)
            prescalar = (T1CON & 0x0030) >> 4
            return self.timer_multipliers[prescalar] * (float(PR1) + 1.)

    def trigger(self):
        if self.connected:
            self.write('SCOPE:TRIGGER')
            return self.get_bufferbin()

    def get_buffer(self):
        if self.connected:
            self.write('SCOPE:BUFFER? 0,{:X}'.format(self.SCOPE_BUFFER_SIZE))
            ret = self.read()
            vals = ret.split(',')
            return [int(val, 16) >> self.num_avg for val in vals]

    def get_bufferbin(self):
        if self.connected:
            self.write('SCOPE:BUFFERBIN? 0,{:X}'.format(self.SCOPE_BUFFER_SIZE))
            ret = b''
            while len(ret) < 2 * self.SCOPE_BUFFER_SIZE:
                bytes_waiting = self.dev.inWaiting()
                if bytes_waiting > 0:
                    ret += self.dev.read(bytes_waiting)
            vals = array.array('H')
            vals.frombytes(ret)
            return [int(val) >> self.num_avg for val in vals]

    def set_period(self, period):
        if self.connected:
            if period > 256. * 65536. * self.TCY:
                return
            elif period > 64. * 65536. * self.TCY:
                T2CON = 0x0030
                PR2 = int(period * (self.FCY / 256.)) - 1
            elif period > 8. * 65536. * self.TCY:
                T2CON = 0x0020
                PR2 = int(period * (self.FCY / 64.)) - 1
            elif period > 65536. * self.TCY:
                T2CON = 0x0010
                PR2 = int(period * (self.FCY / 8.)) - 1
            elif period >= 8. * self.TCY:
                T2CON = 0x0000
                PR2 = int(period * self.FCY) - 1
            else:
                T2CON = 0x0000
                PR2 = 3
            self.write('SCOPE:INTERVAL {:X},{:X}'.format(PR2, T2CON))
            self.sampling_interval = self.get_period()
            self.num_avg = self.get_num_avg()

    def get_period(self):
        if self.connected:
            self.write('SCOPE:INTERVAL?')
            vals = self.read().split(',')
            PR2 = int(vals[0], 16)
            T2CON = int(vals[1], 16)
            prescalar = (T2CON & 0x0030) >> 4
            return self.timer_multipliers[prescalar] * (float(PR2) + 1.)

    def get_sweep_progress(self):
        if self.connected:
            self.write('SCOPE:SWEEP?')
            vals = self.read().split(',')
            return [int(val, 16) for val in vals]

    def sweep_in_progress(self):
        if self.connected:
            return True if self.get_sweep_progress()[0] != 0 else False

    def set_ch1range(self, val):
        if self.connected:
            self.set_ch1gain(val)
            self.ch1_range = self.get_ch1range()

    def get_ch1range(self):
        if self.connected:
            return self.get_ch1gain()

    def set_ch2range(self, val):
        if self.connected:
            self.set_ch2gain(val)
            self.ch2_range = self.get_ch2range()

    def get_ch2range(self):
        if self.connected:
            return self.get_ch2gain()

    def set_max_avg(self, val):
        if self.connected:
            self.write('SCOPE:MAXAVG {:X}'.format(val))
            self.num_avg = self.get_num_avg()

    def get_max_avg(self):
        if self.connected:
            self.write('SCOPE:MAXAVG?')
            return int(self.read(), 16)

    def get_num_avg(self):
        if self.connected:
            self.write('SCOPE:NUMAVG?')
            return int(self.read(), 16)

    def set_wgrange(self, val):
        if self.connected:
            self.write('WAVEGEN:GAIN {:X}'.format(int(val)))

    def get_wgrange(self):
        if self.connected:
            self.write('WAVEGEN:GAIN?')
            return int(self.read(), 16)

    def set_shape_val(self, val):
        if self.connected:
            self.write('WAVEGEN:SHAPE {:X}'.format(int(val)))

    def get_shape_val(self):
        if self.connected:
            self.write('WAVEGEN:SHAPE?')
            return int(self.read(), 16)

    def set_freq_vals(self, val1, val2):
        if self.connected:
            self.write('WAVEGEN:FREQ {:X},{:X}'.format(int(val1), int(val2)))

    def get_freq_vals(self):
        if self.connected:
            self.write('WAVEGEN:FREQ?')
            ret = self.read()
            vals = ret.split(',')
            return [int(val, 16) for val in vals]

    def set_phase_val(self, val):
        if self.connected:
            self.write('WAVEGEN:PHASE {:X}'.format(int(val)))

    def get_phase_val(self):
        if self.connected:
            self.write('WAVEGEN:PHASE?')
            return int(self.read(), 16)

    def set_amplitude_val(self, val):
        if self.connected:
            self.write('WAVEGEN:AMPLITUDE {:X}'.format(int(val)))

    def get_amplitude_val(self):
        if self.connected:
            self.write('WAVEGEN:AMPLITUDE?')
            return int(self.read(), 16)

    def set_offset_val(self, val):
        if self.connected:
            self.write('WAVEGEN:OFFSET {:X}'.format(int(val)))

    def get_offset_val(self):
        if self.connected:
            self.write('WAVEGEN:OFFSET?')
            return int(self.read(), 16)

    def set_sq_offset_adj(self, val):
        if self.connected:
            self.write('WAVEGEN:SQADJ {:X}'.format(int(val)))

    def get_sq_offset_adj(self):
        if self.connected:
            self.write('WAVEGEN:SQADJ?')
            return int(self.read(), 16)

    def set_nsq_offset_adj(self, val):
        if self.connected:
            self.write('WAVEGEN:NSQADJ {:X}'.format(int(val)))

    def get_nsq_offset_adj(self):
        if self.connected:
            self.write('WAVEGEN:NSQADJ?')
            return int(self.read(), 16)

    def set_freq(self, freq):
        if self.connected:
            freq_reg_val = int(268435456. * freq / self.MCLK_FREQ + 0.5)
            high_14bits = freq_reg_val >> 14
            low_14bits = freq_reg_val & 0x3FFF
            self.set_freq_vals(low_14bits, high_14bits)

    def get_freq(self):
        if self.connected:
            vals = self.get_freq_vals()
            freq_reg_val = vals[0] + (vals[1] << 14)
            return self.MCLK_FREQ * float(freq_reg_val) / 268435456.

    def set_phase(self, phase):
        if self.connected:
            phase_val = math.fmod(phase, 360.)
            if phase_val >= 0.:
                phase_reg_val = int(4096. * phase_val / 360. + 0.5)
            else:
                phase_reg_val = int(4096. * (360. - phase_val) / 360. + 0.5)             
            self.set_phase_val(phase_reg_val)

    def get_phase(self):
        if self.connected:
            return 360. * float(self.get_phase_val()) / 4096.

    def set_shape(self, shape):
        if self.connected:
            if shape in self.shapes:
                self.set_shape_val(self.shapes.index(shape))
            else:
                print("Valid waveform shapes are 'DC', 'SIN', 'SQUARE', and 'TRIANGLE'.")

    def get_shape(self):
        if self.connected:
            return self.shapes[self.get_shape_val()]

    def set_amplitude(self, amplitude):
        if self.connected:
            shape = self.get_shape()
            wg_range = self.get_wgrange()
            if (amplitude > 2.5) or (amplitude < 0.):
                pass
#                print("Valid waveform amplitudes are between 0V and 2.5V.")
            elif (wg_range == 0 and amplitude >= 0.95) or (wg_range == 1 and amplitude >= 0.9):
                gain = self.wg_sq_gain[1] if shape == 'SQUARE' else self.wg_nsq_gain[1]
                self.set_amplitude_val(int(amplitude / (10e-3 * gain) + 0.5))
                self.set_wgrange(1)
            else:
                gain = self.wg_sq_gain[0] if shape == 'SQUARE' else self.wg_nsq_gain[0]
                self.set_amplitude_val(int(amplitude / (4e-3 * gain) + 0.5))
                self.set_wgrange(0)

    def get_amplitude(self):
        if self.connected:
            volts_per_lsb = (4e-3, 10e-3)
            shape = self.get_shape()
            wg_range = self.get_wgrange()
            amplitude_val = self.get_amplitude_val()
            if shape == 'SQUARE':
                return volts_per_lsb[wg_range] * self.wg_sq_gain[wg_range] * float(amplitude_val)
            else:
                return volts_per_lsb[wg_range] * self.wg_nsq_gain[wg_range] * float(amplitude_val)

    def set_offset(self, offset):
        if self.connected:
            if (offset > 5.) or (offset < 0.):
                pass
#                print("Valid waveform offsets are between 0V and 5V.")
            else:
                val = int(offset / (5e-3 * self.vo_gain) + self.vo_zero + 0.5)
                val = val if val > 0 else 0
                val = val if val < 1023 else 1023
                self.set_offset_val(val)

    def get_offset(self):
        if self.connected:
            return 5e-3 * self.vo_gain * (float(self.get_offset_val()) - self.vo_zero)

    def wave(self, **kwargs):
        if self.connected:
            freq = kwargs.get('freq', None)
            phase = kwargs.get('phase', None)
            shape = kwargs.get('shape', None)
            amplitude = kwargs.get('amplitude', None)
            offset = kwargs.get('offset', None)

            if freq is not None:
                self.set_freq(freq)
            if phase is not None:
                self.set_phase(phase)
            if shape is not None:
                self.set_shape(shape)
            if amplitude is not None:
                self.set_amplitude(amplitude)
            if offset is not None:
                self.set_offset(offset)

    def read_flash(self, address, num_bytes):
        if self.connected:
            self.write('FLASH:READ {:X},{:X},{:X}'.format(int(address) >> 16, int(address) & 0xFFFF, int(num_bytes)))
            ret = self.read()
            vals = ret.split(',')
            return [int(val, 16) for val in vals]

    def write_flash(self, address, values):
        if self.connected:
            cmd = 'FLASH:WRITE {:X},{:X}'.format(int(address) >> 16, int(address) & 0xFFFF)
            for value in values:
                cmd += ',{:X}'.format(int(value & 0xFF))
            self.write(cmd)

    def erase_flash(self, address):
        if self.connected:
            self.write('FLASH:ERASE {:X},{:X}'.format(int(address) >> 16, int(address) & 0xFFFF))

    def read_calibration_vals(self):
        if self.connected:
            for num_avg in range(5):
                for ch_range in range(2):
                    vals = self.read_flash(0x10000 + 2 * (2 * num_avg + ch_range), 4)
                    if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                        self.ch1_zero[num_avg][ch_range] = (vals[0] + 256 * vals[1]) / 16.

            for num_avg in range(5):
                for ch_range in range(2):
                    vals = self.read_flash(0x10014 + 2 * (2 * num_avg + ch_range), 4)
                    if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                        self.ch2_zero[num_avg][ch_range] = (vals[0] + 256 * vals[1]) / 16.

            for ch_range in range(2):
                vals = self.read_flash(0x10028 + 2 * ch_range, 4)
                if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                    self.ch1_zero_4MSps[ch_range] = (vals[0] + 256 * vals[1]) / 16.

            for ch_range in range(2):
                vals = self.read_flash(0x1002C + 2 * ch_range, 4)
                if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                    self.ch2_zero_4MSps[ch_range] = (vals[0] + 256 * vals[1]) / 16.

            for num_avg in range(5):
                for ch_range in range(2):
                    vals = self.read_flash(0x10030 + 2 * (2 * num_avg + ch_range), 4)
                    if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                        self.ch1_gain[num_avg][ch_range] = (vals[0] + 256 * vals[1]) / 32768.

            for num_avg in range(5):
                for ch_range in range(2):
                    vals = self.read_flash(0x10044 + 2 * (2 * num_avg + ch_range), 4)
                    if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                        self.ch2_gain[num_avg][ch_range] = (vals[0] + 256 * vals[1]) / 32768.

            for ch_range in range(2):
                vals = self.read_flash(0x10058 + 2 * ch_range, 4)
                if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                    self.ch1_gain_4MSps[ch_range] = (vals[0] + 256 * vals[1]) / 32768.

            for ch_range in range(2):
                vals = self.read_flash(0x1005C + 2 * ch_range, 4)
                if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                    self.ch2_gain_4MSps[ch_range] = (vals[0] + 256 * vals[1]) / 32768.

            vals = self.read_flash(0x10060, 4)
            if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                self.set_sq_offset_adj(vals[0] + 256 * vals[1])

            vals = self.read_flash(0x10062, 4)
            if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                self.set_nsq_offset_adj(vals[0] + 256 * vals[1])

            for wg_range in range(2):
                vals = self.read_flash(0x10064 + 2 * wg_range, 4)
                if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                    self.wg_sq_gain[wg_range] = (vals[0] + 256 * vals[1]) / 32768.

            for wg_range in range(2):
                vals = self.read_flash(0x10068 + 2 * wg_range, 4)
                if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                    self.wg_nsq_gain[wg_range] = (vals[0] + 256 * vals[1]) / 32768.

            vals = self.read_flash(0x1006C, 4)
            if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                self.vo_gain = (vals[0] + 256 * vals[1]) / 32768.

            vals = self.read_flash(0x1006E, 4)
            if (vals[0] != 255) or (vals[1] != 255) or (vals[2] != 255):
                val = ((vals[0] + 256 * vals[1]) & 0x7FFF) / 32.
                self.vo_zero = val if vals[1] < 128 else -val

    def write_calibration_vals(self):
        if self.connected:
            self.erase_flash(0x10000)

            for num_avg in range(5):
                vals = []
                for ch_range in range(2):
                    val = int(round(16. * self.ch1_zero[num_avg][ch_range]))
                    vals.append(val & 0x00FF)
                    vals.append(val >> 8)
                    vals.append(0)
                    vals.append(0)
                self.write_flash(0x10000 + 4 * num_avg, vals)
                read_vals = self.read_flash(0x10000 + 4 * num_avg, len(vals))
                if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                    print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10000 + 4 * num_avg, vals, read_vals))

            for num_avg in range(5):
                vals = []
                for ch_range in range(2):
                    val = int(round(16. * self.ch2_zero[num_avg][ch_range]))
                    vals.append(val & 0x00FF)
                    vals.append(val >> 8)
                    vals.append(0)
                    vals.append(0)
                self.write_flash(0x10014 + 4 * num_avg, vals)
                read_vals = self.read_flash(0x10014 + 4 * num_avg, len(vals))
                if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                    print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10014 + 4 * num_avg, vals, read_vals))

            vals = []
            for ch_range in range(2):
                val = int(round(16. * self.ch1_zero_4MSps[ch_range]))
                vals.append(val & 0x00FF)
                vals.append(val >> 8)
                vals.append(0)
                vals.append(0)
            self.write_flash(0x10028, vals)
            read_vals = self.read_flash(0x10028, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10028, vals, read_vals))

            vals = []
            for ch_range in range(2):
                val = int(round(16. * self.ch2_zero_4MSps[ch_range]))
                vals.append(val & 0x00FF)
                vals.append(val >> 8)
                vals.append(0)
                vals.append(0)
            self.write_flash(0x1002C, vals)
            read_vals = self.read_flash(0x1002C, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x1002C, vals, read_vals))

            for num_avg in range(5):
                vals = []
                for ch_range in range(2):
                    val = int(round(32768. * self.ch1_gain[num_avg][ch_range]))
                    vals.append(val & 0x00FF)
                    vals.append(val >> 8)
                    vals.append(0)
                    vals.append(0)
                self.write_flash(0x10030 + 4 * num_avg, vals)
                read_vals = self.read_flash(0x10030 + 4 * num_avg, len(vals))
                if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                    print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10030 + 4 * num_avg, vals, read_vals))

            for num_avg in range(5):
                vals = []
                for ch_range in range(2):
                    val = int(round(32768. * self.ch2_gain[num_avg][ch_range]))
                    vals.append(val & 0x00FF)
                    vals.append(val >> 8)
                    vals.append(0)
                    vals.append(0)
                self.write_flash(0x10044 + 4 * num_avg, vals)
                read_vals = self.read_flash(0x10044 + 4 * num_avg, len(vals))
                if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                    print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10044 + 4 * num_avg, vals, read_vals))

            vals = []
            for ch_range in range(2):
                val = int(round(32768. * self.ch1_gain_4MSps[ch_range]))
                vals.append(val & 0x00FF)
                vals.append(val >> 8)
                vals.append(0)
                vals.append(0)
            self.write_flash(0x10058, vals)
            read_vals = self.read_flash(0x10058, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10058, vals, read_vals))

            vals = []
            for ch_range in range(2):
                val = int(round(32768. * self.ch2_gain_4MSps[ch_range]))
                vals.append(val & 0x00FF)
                vals.append(val >> 8)
                vals.append(0)
                vals.append(0)
            self.write_flash(0x1005C, vals)
            read_vals = self.read_flash(0x1005C, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x1005C, vals, read_vals))

            vals = []
            val = self.get_sq_offset_adj()
            vals.append(val & 0x00FF)
            vals.append(val >> 8)
            vals.append(0)
            vals.append(0)

            val = self.get_nsq_offset_adj()
            vals.append(val & 0x00FF)
            vals.append(val >> 8)
            vals.append(0)
            vals.append(0)

            self.write_flash(0x10060, vals)
            read_vals = self.read_flash(0x10060, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10060, vals, read_vals))

            vals = []
            for wg_range in range(2):
                val = int(round(32768. * self.wg_sq_gain[wg_range]))
                vals.append(val & 0x00FF)
                vals.append(val >> 8)
                vals.append(0)
                vals.append(0)

            self.write_flash(0x10064, vals)
            read_vals = self.read_flash(0x10064, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10064, vals, read_vals))

            vals = []
            for wg_range in range(2):
                val = int(round(32768. * self.wg_nsq_gain[wg_range]))
                vals.append(val & 0x00FF)
                vals.append(val >> 8)
                vals.append(0)
                vals.append(0)

            self.write_flash(0x10068, vals)
            read_vals = self.read_flash(0x10068, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x10068, vals, read_vals))

            vals = []
            val = int(round(32768. * self.vo_gain))
            vals.append(val & 0x00FF)
            vals.append(val >> 8)
            vals.append(0)
            vals.append(0)

            val = int(round(32. * abs(self.vo_zero))) | (0x8000 if self.vo_zero < 0 else 0x0000)
            vals.append(val & 0x00FF)
            vals.append(val >> 8)
            vals.append(0)
            vals.append(0)

            self.write_flash(0x1006C, vals)
            read_vals = self.read_flash(0x1006C, len(vals))
            if not all([read_vals[i] == vals[i] for i in range(len(vals))]):
                print("Problem writing calibration values at {:X}: wrote {!s} but read {!s}.".format(0x1006C, vals, read_vals))

