const app = Vue.createApp({
    data() {
        return { logs: [], chart: null }
    },
    methods: {
        async updateData() {
            try {
                const res = await fetch(`/api/data?t=${new Date().getTime()}`);
                const data = await res.json();
                this.logs = data.logs || [];
                if (this.logs.length > 0) {
                    this.renderChart();
                }
            } catch (e) { 
                console.error("Flask Offline"); 
            }
        },
        renderChart() {
            const ctx = document.getElementById('myChart').getContext('2d');
            if (this.chart) this.chart.destroy();
            
            const d = [...this.logs].reverse();
            
            this.chart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: d.map(l => l.time),
                    datasets: [{
                        label: 'Level Air (cm)',
                        data: d.map(l => l.level),
                        borderColor: '#00d4ff',
                        tension: 0.4,
                        fill: true,
                        backgroundColor: 'rgba(0, 212, 255, 0.1)'
                    }]
                },
                options: { 
                    responsive: true, 
                    maintainAspectRatio: false, 
                    animation: false,
                    scales: {
                        y: {
                            min: 0,
                            max: 400,
                            ticks: { stepSize: 50, color: '#94a3b8' },
                            grid: { color: 'rgba(255, 255, 255, 0.1)' }
                        },
                        x: { 
                            ticks: { color: '#94a3b8' },
                            grid: { display: false } 
                        }
                    },
                    plugins: {
                        legend: { display: false }
                    }
                }
            });
        },
        async sendCmd(cmd) {
            // Notifikasi Konfirmasi Modern
            Swal.fire({
                title: 'Konfirmasi',
                text: `Apakah Anda yakin ingin mematikan/menyalakan pompa (PAKSA ${cmd})?`,
                icon: 'warning',
                showCancelButton: true,
                confirmButtonColor: cmd === 'ON' ? '#28a745' : '#ff4d4d',
                cancelButtonColor: '#6e7881',
                confirmButtonText: 'Iya, Lanjutkan!',
                cancelButtonText: 'Tidak',
                background: '#1e293b',
                color: '#fff'
            }).then(async (result) => {
                if (result.isConfirmed) {
                    try {
                        await fetch('/api/control', {
                            method: 'POST',
                            headers: { 'Content-Type': 'application/json' },
                            body: JSON.stringify({ command: cmd })
                        });
                        
                        Swal.fire({
                            title: 'Berhasil!',
                            text: `Perintah ${cmd} terkirim.`,
                            icon: 'success',
                            background: '#1e293b',
                            color: '#fff',
                            timer: 1500,
                            showConfirmButton: false
                        });
                        
                        this.updateData(); // Langsung perbarui data
                    } catch (e) {
                        Swal.fire('Gagal!', 'Terjadi kesalahan pada server.', 'error');
                    }
                }
            });
        }
    },
    mounted() {
        this.updateData();
        setInterval(this.updateData, 3000);
    }
}).mount('#app');