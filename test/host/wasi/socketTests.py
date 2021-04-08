#!/usr/bin/env python3
import subprocess
import unittest

class SocketTest(unittest.TestCase):
    def test_dummy(self):
        self.assertTrue(True)

    def test_tcp_communicate(self):
        with subprocess.Popen(['./TCPserver']) as server:
            client = subprocess.run(['./TCPclient'], capture_output=True, timeout=1)
            self.assertEqual(client.returncode, 0)
            self.assertEqual(client.stdout, b'negordyh')

            server.wait(timeout=3)
            self.assertEqual(server.returncode, 0)

    def test_tcp_wasi_server(self):
        pass

    def test_tcp_wasi_client(self):
        pass

if __name__ == '__main__':
    unittest.main()
